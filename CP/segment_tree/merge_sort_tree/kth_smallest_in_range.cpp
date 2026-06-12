#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: K-th Smallest in Range
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Ek array size n
 *   - Q queries, har query = (L, R, K)
 *
 * Poochna hai:
 *   - Index range [L..R] ke elements ko sort karo
 *   - K-th smallest element batao (K = 1-indexed)
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   Query (0, 4, 3):
 *     range values = {5,1,2,3,4} → sorted {1,2,3,4,5}
 *     3rd smallest = 3
 *
 *   Query (1, 4, 2):
 *     range values = {1,2,3,4} → sorted same
 *     2nd smallest = 2
 *
 *   Query (0, 2, 1):
 *     range values = {5,1,2} → sorted {1,2,5}
 *     1st smallest = 1
 *
 * APPROACH: Merge Sort Tree + Binary Search on Answer
 *   countLessEqual se pata chalta hai kitne <= v
 *   sabse chhota v jahan count >= K → wahi K-th smallest
 *
 * Time: O(log² n) per query
 * SIMILAR: SPOJ KQUERY | range median (special case)
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n, loVal, hiVal;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * ---------------------
     * Har node = us segment ka sorted vector.
     * Leaf: {arr[l]} | Internal: merge(left child, right child)
     *
     * Jaise merge sort me do sorted halves jodte hain, waise hi yahan.
     */
    void build(const vector<int>& arr, int node, int l, int r) {
        if (l == r) { tree[node] = {arr[l]}; return; }
        int mid = (l + r) / 2;
        build(arr, 2 * node + 1, l, mid);
        build(arr, 2 * node + 2, mid + 1, r);
        const auto& a = tree[2 * node + 1], &b = tree[2 * node + 2];
        tree[node].resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), tree[node].begin());
    }

    /*
     * countLessEqual(ql, qr, x, node, l, r)
     * -------------------------------------
     * [ql..qr] me kitne elements <= x ?
     * kthSmallest ke har BS step me ye call hota hai.
     *
     * Full overlap: upper_bound(x) on sorted tree[node]
     */
    int countLessEqual(int ql, int qr, int x, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());
        int mid = (l + r) / 2;
        return countLessEqual(ql, qr, x, 2 * node + 1, l, mid)
             + countLessEqual(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

public:
    /*
     * Constructor
     * array se tree build, min/max value store (BS bounds)
     */
    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, {});
        loVal = *min_element(arr.begin(), arr.end());
        hiVal = *max_element(arr.begin(), arr.end());
        build(arr, 0, 0, n - 1);
    }

    /*
     * kthSmallest(L, R, K)
     * --------------------
     * Step 1: lo = sabse chhoti value, hi = sabse badi value
     * Step 2: Binary search on [lo, hi]:
     *           mid try karo
     *           agar [L,R] me <= mid wale >= K elements → answer <= mid
     *           warna answer > mid
     * Step 3: return lo (final answer)
     *
     * Kyun sahi?
     *   count(<=v) v badhne par badhta hai (monotonic)
     *   pehla v jahan count >= K → exactly K-th smallest
     */
    int kthSmallest(int L, int R, int K) const {
        int lo = loVal, hi = hiVal;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (countLessEqual(L, R, mid, 0, 0, n - 1) >= K) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    vector<tuple<int,int,int>> queries = {{0,4,3}, {1,4,2}, {0,2,1}};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n-- K-th Smallest Queries --\n";

    for (auto& [L, R, K] : queries)
        cout << "kthSmallest [" << L << "," << R << "] k=" << K
             << " -> " << mst.kthSmallest(L, R, K) << "\n";

    return 0;
}
