/*
 * ============================================================================
 * TOPIC    : Square Root Decomposition
 * FILE     : sqrt_range_min_query.cpp
 * PROBLEM  : Range minimum query with point updates
 * APPROACH : Blocks of size sqrt(n) — lazy block recompute
 * COMPLEX  : Query/Update O(sqrt n)  |  Build O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SQRT DECOMPOSITION — Range Minimum Query + Point Update
// ────────────────────────────────────────────────────────────────────────────
// Idea: array ko sqrt(n) size ke blocks me todo. Har block ka MINIMUM pehle
// se store karo (blockMin). Range min query me teen hisse:
//   1) left partial  -> elements scan karke min lo
//   2) full blocks   -> seedha blockMin use karo
//   3) right partial -> elements scan karke min lo
//
// Update pe: element badlo, phir us block ka min dobara nikaalo (recompute).
//
// Params:
//   blockSize  -> ~sqrt(n)
//   blockMin[b]-> block b ka minimum
//   idx/blockSize -> element ka block number
//
// Complexity: Build O(n) | Query O(sqrt n) | Update O(sqrt n)
// ════════════════════════════════════════════════════════════════════════════

struct SqrtRMQ {
    vector<int> a;         // original array
    vector<int> blockMin;  // har block ka minimum
    int n, blockSize, numBlocks;

    // ── Constructor: array lo, blocks banao, har block ka min nikaalo ───────
    //   1) a = arr copy, blockSize = max(1, sqrt(n))
    //   2) numBlocks calculate, blockMin sab INT_MAX se start
    //   3) har element ko scan karke apne block ka min update karo
    //   4) ab har block ka minimum precomputed — query me fast use
    SqrtRMQ(const vector<int> &arr) : a(arr) {
        n = a.size();
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockMin.assign(numBlocks, INT_MAX);
        for (int i = 0; i < n; i++)
            blockMin[i / blockSize] = min(blockMin[i / blockSize], a[i]);
    }

    // ── update: index 'idx' pe value 'val' set karo ──────────────────────────
    //   1) a[idx] = val — array me point update
    //   2) us block ka blockMin reset karke poora block dobara scan karo
    //   3) lazy recompute — update O(blockSize) ≈ O(sqrt n)
    void update(int idx, int val) {
        a[idx] = val;
        int b = idx / blockSize;
        blockMin[b] = INT_MAX;
        for (int i = b * blockSize; i < min(n, (b + 1) * blockSize); i++)
            blockMin[b] = min(blockMin[b], a[i]);
    }

    // ── query: range [l, r] ka minimum nikalo ───────────────────────────────
    //   1) left partial: jab tak block boundary na aaye, a[l++] se min lo
    //   2) full blocks: blockMin[l/blockSize] leke l += blockSize
    //   3) right partial: bache elements scan karo
    //   4) ans return — teen-phase approach, O(sqrt n)
    int query(int l, int r) {
        int ans = INT_MAX;

        // left partial block — block start pe align hone tak
        while (l <= r && l % blockSize != 0)
            ans = min(ans, a[l++]);

        // beech ke full blocks — seedha blockMin use
        while (l + blockSize - 1 <= r) {
            ans = min(ans, blockMin[l / blockSize]);
            l += blockSize;
        }

        // right partial block — last incomplete block
        while (l <= r)
            ans = min(ans, a[l++]);

        return ans;
    }
};

int main() {
    vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12};
    SqrtRMQ st(a);
    cout << "RMQ [1,4] = " << st.query(1, 4) << endl;
    st.update(3, 8);
    cout << "After update idx 3 -> 8, RMQ [1,4] = " << st.query(1, 4) << endl;
    return 0;
}
