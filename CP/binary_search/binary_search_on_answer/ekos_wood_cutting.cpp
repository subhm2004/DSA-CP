/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : ekos_wood_cutting.cpp
 * PROBLEM  : Cut trees at height H — get at least M wood (maximize H)
 * APPROACH : BS on answer (cutting height), sum wood collected
 * COMPLEX  : Time: O(n log(maxHeight))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EKO WOOD CUTTING — Maximum cutting height jahan wood >= need
// ────────────────────────────────────────────────────────────────────────────
// BS on answer = height H
// woodCollected(H) = sum of (tree[i] - H) for tree[i] > H
// Height badhao -> kam wood -> monotonic
// MAX answer: wood >= need -> lo=mid+1 (aur uncha try karo)
// ════════════════════════════════════════════════════════════════════════════

// ── woodCollected: height H pe kitna wood milega ───────────────────────────
//   1) har tree jahan h > height, wood += h - height
//   2) total wood return
long long woodCollected(const vector<int> &trees, int height) {
    long long sum = 0;
    for (int h : trees)
        if (h > height)
            sum += h - height;
    return sum;
}

// ── maxCuttingHeight: maximum H jahan need wood mil jaye ────────────────────
//   1) lo=0, hi=max tree height
//   2) woodCollected(mid) >= need -> ans=mid, lo=mid+1
//   3) warna hi=mid-1
int maxCuttingHeight(vector<int> trees, long long need) {
    int lo = 0, hi = *max_element(trees.begin(), trees.end()), ans = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (woodCollected(trees, mid) >= need) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int main() {
    vector<int> trees = {4, 42, 40, 26, 46};
    long long need = 20;
    cout << "Maximum cutting height = " << maxCuttingHeight(trees, need) << endl;
    return 0;
}
