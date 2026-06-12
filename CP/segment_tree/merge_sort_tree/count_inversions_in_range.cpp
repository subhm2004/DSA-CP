#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Count Inversions in Range [L, R]
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Array size n
 *   - Q queries, har query = (L, R)
 *
 * Poochna hai:
 *   - Sirf index range [L..R] ke ANDAR kitne inversion pairs hain?
 *   - Inversion pair = (i, j) jahan L <= i < j <= R  AUR  arr[i] > arr[j]
 *
 * POORI array vs RANGE mein farq:
 *   inversion_count.cpp     → poori array [0, n-1]
 *   YE file                 → sirf query range [L, R]
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   Query (0, 4) — poori array:
 *     (0,1),(0,2),(0,3),(0,4) → 5>1,5>2,5>3,5>4 → 4 inversions
 *
 *   Query (1, 4) — subarray {1,2,3,4}:
 *     koi pair nahi jahan pehla > doosra → 0 inversions
 *
 *   Query (0, 2) — subarray {5,1,2}:
 *     (0,1): 5>1, (0,2): 5>2 → 2 inversions
 *
 * APPROACH: Merge Sort Tree
 *   Har i from L+1 to R:
 *     left side = [L, i-1] (sirf range ke andar)
 *     inversions += (i - L) - countLessEqual(L, i-1, arr[i])
 *
 * Time: O((R-L) * log² n) per query
 * SIMILAR: inversion_count.cpp (full array) | LC 493 (range variants)
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<int> arr;
    vector<vector<int>> tree;

    /*
     * build(node, l, r)
     * Merge sort tree — har node sorted vector
     */
    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {arr[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node + 1, l, mid);
        build(2 * node + 2, mid + 1, r);
        const auto& a = tree[2 * node + 1];
        const auto& b = tree[2 * node + 2];
        tree[node].resize(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), tree[node].begin());
    }

    /*
     * countLessEqual(ql, qr, x, node, l, r)
     * -------------------------------------
     * Index range [ql..qr] me kitne elements <= x ?
     * Range inversion me [L, i-1] par call hota hai.
     */
    int countLessEqual(int ql, int qr, int x, int node, int l, int r) const {
        if (ql > qr || r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());
        int mid = (l + r) / 2;
        return countLessEqual(ql, qr, x, 2 * node + 1, l, mid)
             + countLessEqual(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

public:
    /*
     * Constructor — array store + tree build
     */
    MergeSortTree(const vector<int>& a) : arr(a) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), {});
        if (n > 0) build(0, 0, n - 1);
    }

    /*
     * inversionCountInRange(L, R)
     * ---------------------------
     * Sirf [L..R] ke andar inversion pairs count karo.
     *
     * Har i = L+1 se R tak:
     *   left = indices [L, i-1]  → total (i - L) elements
     *   kitne left elements > arr[i]?
     *     = (i - L) - countLessEqual(L, i-1, arr[i])
     *
     * Walkthrough arr=[5,1,2,3,4], L=0, R=2:
     *   i=1: left=[5], arr[1]=1, leq=0, inv += 1-0 = 1  (5>1)
     *   i=2: left=[5,1], arr[2]=2, leq=1, inv += 2-1 = 1 (5>2)
     *   total = 2 ✓
     *
     * Walkthrough L=1, R=4:
     *   subarray {1,2,3,4} — koi inversion → 0 ✓
     */
    long long inversionCountInRange(int L, int R) const {
        if (n == 0 || L >= R) return 0;
        long long inv = 0;
        for (int i = L + 1; i <= R; ++i) {
            int leftSize = i - L;
            int leq = countLessEqual(L, i - 1, arr[i], 0, 0, n - 1);
            inv += leftSize - leq;
        }
        return inv;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    vector<pair<int, int>> queries = {
        {0, 4}, {1, 4}, {0, 2}, {2, 4}, {1, 3},
    };

    cout << "Array: ";
    for (int i = 0; i < (int)arr.size(); ++i)
        cout << "[" << i << "]=" << arr[i] << " ";
    cout << "\n\n-- Q Queries: inversions in [L,R] --\n";

    for (auto& [L, R] : queries)
        cout << "(" << L << "," << R << ") -> "
             << mst.inversionCountInRange(L, R) << "\n";

    // second example
    vector<int> arr2 = {2, 4, 1, 3, 5};
    MergeSortTree mst2(arr2);
    cout << "\nArray: ";
    for (int i = 0; i < (int)arr2.size(); ++i)
        cout << "[" << i << "]=" << arr2[i] << " ";
    cout << "\n";

    vector<pair<int, int>> queries2 = {{0, 4}, {0, 2}, {2, 4}};
    for (auto& [L, R] : queries2)
        cout << "(" << L << "," << R << ") -> "
             << mst2.inversionCountInRange(L, R) << "\n";

    return 0;
}
