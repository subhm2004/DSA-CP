#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Count Elements Strictly Greater Than K in Range [L, R]
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Array size n
 *   - W queries, har query = (L, R, K)
 *
 * Poochna hai:
 *   - Index range [L..R] me kitne elements ki VALUE strictly > K hai?
 *   - Matlab K se BADE kitne elements hain us range mein
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   Query (0, 4, 3):
 *     range = {5,1,2,3,4}, K=3
 *     3 se bade = {5,4} → answer 2
 *
 *   Query (1, 4, 2):
 *     range = {1,2,3,4}, K=2
 *     2 se bade = {3,4} → answer 2
 *
 *   Query (2, 3, 5):
 *     range = {2,3}, K=5
 *     5 se bade = {} → answer 0
 *
 * DHYAAN: K = threshold VALUE hai, K-th smallest wala K NAHI!
 *
 * APPROACH: Merge Sort Tree → countGreater(L, R, K)
 *   sorted vector pe upper_bound(K):
 *     upper_bound = pehla element > K
 *     uske baad sab > K → count = size - upper_bound index
 *
 * Alternate formula:
 *   countGreater = (R-L+1) - countLessEqual(L,R,K)
 *
 * Time: O(log² n) per query
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * Merge sort tree — har node sorted vector store karta hai
     */
    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = {arr[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        const auto& a = tree[2 * node + 1];
        const auto& b = tree[2 * node + 2];
        tree[node].resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), tree[node].begin());
    }

    /*
     * countGreaterRec(ql, qr, k, node, l, r)
     * --------------------------------------
     * Core: [ql..qr] me kitne elements STRICTLY > k ?
     *
     * Case 1 — no overlap → 0
     * Case 2 — full overlap → upper_bound(k) on sorted vector
     *           upper_bound = pehla element > k
     *           count = tree[node].size() - upper_bound index
     * Case 3 — partial → left + right
     *
     * Example: sorted = {1,2,3,4,5}, k=3
     *   upper_bound(3) at index 3 (element 4)
     *   count = 5 - 3 = 2 (elements 4 aur 5)
     *
     * countSmaller vs countGreater:
     *   countLess uses lower_bound  → elements < k
     *   countGreater uses upper_bound trick → elements > k
     */
    int countGreaterRec(int ql, int qr, int k, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) {
            const auto& v = tree[node];
            int idx = (int)(upper_bound(v.begin(), v.end(), k) - v.begin());
            return (int)v.size() - idx;
        }

        int mid = (l + r) / 2;
        return countGreaterRec(ql, qr, k, 2 * node + 1, l, mid)
             + countGreaterRec(ql, qr, k, 2 * node + 2, mid + 1, r);
    }

public:
    /*
     * Constructor — array se poora tree build
     */
    MergeSortTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), {});
        if (n > 0) build(arr, 0, 0, n - 1);
    }

    /*
     * countGreater(L, R, K)
     * ---------------------
     * Har W query ke liye ye function call karo.
     * Return = [L,R] me kitne elements ki value > K
     *
     * Verify: countSmaller + countGreater + countEqual = (R-L+1)
     *   countEqual = elements == K (alag query se nikal sakte ho)
     */
    int countGreater(int L, int R, int K) const {
        if (n == 0 || L > R) return 0;
        return countGreaterRec(L, R, K, 0, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    vector<tuple<int, int, int>> queries = {
        {0, 4, 3}, {1, 4, 2}, {2, 3, 5}, {0, 2, 1}, {3, 4, 4},
    };

    cout << "Array: ";
    for (int i = 0; i < (int)arr.size(); ++i)
        cout << "[" << i << "]=" << arr[i] << " ";
    cout << "\n\n-- W Queries: count elements > K in [L,R] --\n";

    for (auto& [L, R, K] : queries)
        cout << "(" << L << "," << R << "," << K << ") -> "
             << mst.countGreater(L, R, K) << "\n";

    return 0;
}
