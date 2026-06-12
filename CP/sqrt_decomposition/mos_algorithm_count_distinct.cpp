#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * MO'S ALGORITHM — Count Distinct Elements in Range
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM (classic FAANG / CP):
 *   Static array, Q queries: har query (L,R) → [L,R] me kitne DISTINCT elements?
 *
 * Example: arr = [1, 2, 1, 3, 2, 1]
 *   (0,5) → {1,2,3} = 3 distinct
 *   (1,3) → {2,1,3} = 3 distinct
 *   (2,5) → {1,3,2} = 3 distinct
 *   (0,2) → {1,2}   = 2 distinct
 *
 * NAIVE: har query O(n) → O(Q*n)
 * MO'S:   O((n+Q)*sqrt(n)) offline — queries ko smart order me process
 *
 * CORE IDEA:
 *   block = sqrt(n)
 *   Queries sort: pehle L/block, phir R (zigzag — even block ↑, odd block ↓)
 *   Do pointers curL, curR — expand/shrink karke answer maintain karo
 *
 * Time: O((n+Q) * sqrt(n))  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

struct Query {
    int l, r, idx;
};

/*
 * countDistinctMo(arr, queries)
 * -----------------------------
 * Offline Mo's algorithm se har range me distinct count.
 *
 * Step 1: blockSize = sqrt(n)
 * Step 2: queries ko Mo order me sort:
 *           - pehle l/block se
 *           - same left block me: even block → r ascending, odd → r descending
 *             (zigzag — curR ko zyada move nahi karna padta)
 * Step 3: curL, curR, freq[], distinct maintain karke har query answer
 */
vector<int> countDistinctMo(const vector<int>& arr, vector<pair<int, int>>& queries) {
    int n = (int)arr.size();
    int q = (int)queries.size();
    int block = max(1, (int)sqrt(n));

    vector<Query> qs(q);
    for (int i = 0; i < q; i++)
        qs[i] = {queries[i].first, queries[i].second, i};

    auto cmp = [&](const Query& a, const Query& b) {
        int ba = a.l / block, bb = b.l / block;
        if (ba != bb) return ba < bb;
        if (ba & 1) return a.r > b.r;  // odd left block → r descending
        return a.r < b.r;                 // even → r ascending
    };
    sort(qs.begin(), qs.end(), cmp);

    vector<int> ans(q);
    vector<int> freq(n + 1, 0);
    int distinct = 0;
    int curL = 0, curR = -1;

    auto add = [&](int idx) {
        if (freq[arr[idx]] == 0) distinct++;
        freq[arr[idx]]++;
    };
    auto remove = [&](int idx) {
        freq[arr[idx]]--;
        if (freq[arr[idx]] == 0) distinct--;
    };

    for (const auto& qu : qs) {
        while (curR < qu.r) add(++curR);
        while (curL > qu.l) add(--curL);
        while (curR > qu.r) remove(curR--);
        while (curL < qu.l) remove(curL++);
        ans[qu.idx] = distinct;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {1, 2, 1, 3, 2, 1};
    vector<pair<int, int>> queries = {{0, 5}, {1, 3}, {2, 5}, {0, 2}};

    vector<int> res = countDistinctMo(arr, queries);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n-- Count distinct (Mo's Algorithm) --\n";
    for (int i = 0; i < (int)queries.size(); i++)
        cout << "  [" << queries[i].first << "," << queries[i].second << "] -> "
             << res[i] << " distinct\n";

    return 0;
}
