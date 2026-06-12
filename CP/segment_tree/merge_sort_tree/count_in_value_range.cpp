#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Count Elements in Value Range [A,B] inside Index Range [L,R]
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Array size n
 *   - Queries jahan tumhe DO ranges deni hain:
 *       INDEX range [L, R]  — array ke kaunse indices
 *       VALUE range [A, B]  — element ki value kis range me honi chahiye
 *
 * Poochna hai:
 *   - [L..R] indices ke elements me se kitne ki VALUE [A..B] me hai?
 *   - [A,B] inclusive hai (A aur B dono count honge)
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   Query L=1, R=4, A=2, B=4:
 *     indices 1..4 → values {1, 2, 3, 4}
 *     [2,4] me {2, 3, 4} → answer 3
 *
 *   Query L=0, R=4, A=1, B=3:
 *     poori array → values {5,1,2,3,4}
 *     [1,3] me {1, 2, 3} → answer 3
 *
 * FORMULA:
 *   countInRange = count(<=B) - count(<A)
 *
 * APPROACH: Merge Sort Tree
 * Time: O(log² n) per query
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * ---------------------
     * Standard merge sort tree build.
     * Leaf = {arr[l]}, Internal = merge(left, right) sorted.
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
     * countLess(ql, qr, x, node, l, r)
     * --------------------------------
     * [ql..qr] me STRICTLY < x wale kitne elements?
     *
     * Full overlap: lower_bound(x) — pehla >= x, usse pehle sab < x
     *
     * Ye function countInRange me count(< A) ke liye use hota hai.
     */
    int countLess(int ql, int qr, int x, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());
        int mid = (l + r) / 2;
        return countLess(ql, qr, x, 2 * node + 1, l, mid)
             + countLess(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

    /*
     * countLessEqual(ql, qr, x, node, l, r)
     * -------------------------------------
     * [ql..qr] me <= x wale kitne elements?
     *
     * Full overlap: upper_bound(x) — pehla > x, usse pehle sab <= x
     *
     * Ye function countInRange me count(<= B) ke liye use hota hai.
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
     * Constructor — n set, tree size 4*n, build from root
     */
    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, {});
        build(arr, 0, 0, n - 1);
    }

    /*
     * countInRange(L, R, A, B)
     * ------------------------
     * Main query function.
     *
     *   count(<=B) - count(<A) = elements with A <= value <= B
     *
     * Kyun kaam karta hai?
     *   countLE(B) me sab included jo <= B (chahe < A bhi ho)
     *   countLess(A) me sirf < A wale
     *   subtract → sirf [A,B] bachte hain
     *
     * Example: {1,2,3,4}, A=2, B=4
     *   countLE(4)=4, countLess(2)=1 → 4-1=3 ✓
     */
    int countInRange(int L, int R, int A, int B) const {
        return countLessEqual(L, R, B, 0, 0, n - 1) - countLess(L, R, A, 0, 0, n - 1);
    }

    /*
     * countLessThan(L, R, x)
     * Shortcut — sirf < x count (A=B type queries ke liye useful)
     */
    int countLessThan(int L, int R, int x) const {
        return countLess(L, R, x, 0, 0, n - 1);
    }
};

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";

    cout << "countInRange [1,4] value [2,4] -> " << mst.countInRange(1, 4, 2, 4) << "\n";
    cout << "countInRange [0,4] value [1,3] -> " << mst.countInRange(0, 4, 1, 3) << "\n";
    cout << "countLessThan [0,4] x=3        -> " << mst.countLessThan(0, 4, 3) << "\n";

    return 0;
}
