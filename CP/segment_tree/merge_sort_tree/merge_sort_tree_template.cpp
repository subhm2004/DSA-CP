#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * MERGE SORT TREE — Master Template (Poora Class)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE (general):
 *   Tumhare paas ek STATIC array hai (updates kam/nahi).
 *   Range queries chahiye jahan element ki VALUE matter karti hai:
 *     - [L,R] me kitne elements < X ?
 *     - [L,R] me K-th smallest kaunsa ?
 *     - [L,R] me kitne elements value [A,B] me ?
 *
 * NORMAL SEGMENT TREE kyun nahi?
 *   Normal seg tree sum/min/max rakhta hai — ORDER (rank) nahi pata chalta.
 *   Merge Sort Tree har node pe SORTED LIST rakhta hai → order statistics possible.
 *
 * YE SEGMENT TREE HAI?
 *   Haan! Same binary tree, same 3 query cases.
 *   Bas node ki value = ek number nahi, poora sorted vector hai.
 *
 * COMPLEXITY:
 *   Build  : O(n log n)
 *   Query  : O(log² n)
 *   Space  : O(n log n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;                      // array ki length
    int loVal, hiVal;           // array ki min/max value — kthSmallest BS ke liye
    vector<vector<int>> tree;   // tree[node] = us segment ke elements (sorted)

    /*
     * build(arr, node, l, r)
     * ---------------------
     * Merge sort tree RECURSIVELY banata hai.
     *
     * Parameters samjho:
     *   node → tree array mein current index (root = 0)
     *   l, r → ye node array ke indices [l..r] cover karta hai
     *
     * Base case: l == r (leaf)
     *   Sirf ek element → tree[node] = {arr[l]}
     *
     * Recursive case:
     *   mid = (l+r)/2
     *   left child  covers [l, mid]     → node = 2*node+1
     *   right child covers [mid+1, r]   → node = 2*node+2
     *   dono ke sorted vectors ko merge() se jod ke parent mein daalo
     *
     * Visual (arr = [5,1,2,3,4]):
     *              [0────4] → {1,2,3,4,5}
     *             /        \
     *      [0─2]{1,2,5}    [3─4]{3,4}
     *
     * Time: O(n log n) — har level par total n elements merge hote hain
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
     * countLessRec(ql, qr, x, node, l, r)
     * ------------------------------------
     * CORE QUERY: index range [ql..qr] me kitne elements ki VALUE < x ?
     *
     * Segment tree ke 3 cases:
     *
     *   Case 1 — NO OVERLAP (r < ql || l > qr):
     *     Is node ka segment query se bilkul bahar → return 0
     *
     *   Case 2 — FULL OVERLAP (ql <= l && r <= qr):
     *     Poora node segment query ke andar hai.
     *     tree[node] already SORTED hai → binary search:
     *       lower_bound(x) = pehla index jahan element >= x
     *       us index se pehle sab elements < x hain
     *
     *   Case 3 — PARTIAL OVERLAP:
     *     Left + right child ka answer jodo
     *
     * Example: arr=[5,1,2,3,4], query countLess(0,4,3)
     *   values < 3 → {1,2} → answer 2
     *
     * Time: O(log² n)
     */
    int countLessRec(int ql, int qr, int x, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());

        int mid = (l + r) / 2;
        return countLessRec(ql, qr, x, 2 * node + 1, l, mid)
             + countLessRec(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

    /*
     * countLessEqualRec(ql, qr, x, node, l, r)
     * -----------------------------------------
     * [ql..qr] me kitne elements <= x ?
     *
     * Full overlap pe upper_bound(x):
     *   upper_bound = pehla element STRICTLY > x
     *   usse pehle sab <= x
     *
     * Farq samjho:
     *   countLess(3)      → 2  (elements 1,2)
     *   countLessEqual(3) → 3  (elements 1,2,3)
     */
    int countLessEqualRec(int ql, int qr, int x, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());

        int mid = (l + r) / 2;
        return countLessEqualRec(ql, qr, x, 2 * node + 1, l, mid)
             + countLessEqualRec(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

public:
    /*
     * MergeSortTree(arr) — Constructor
     * --------------------------------
     * Step 1: n set karo, tree size = 4*n (segment tree padding)
     * Step 2: loVal = min element, hiVal = max element
     * Step 3: build(0, 0, n-1) se poora tree ready
     */
    MergeSortTree(const vector<int>& arr) {
        n = (int)arr.size();
        tree.assign(4 * max(n, 1), {});
        if (n == 0) return;
        loVal = *min_element(arr.begin(), arr.end());
        hiVal = *max_element(arr.begin(), arr.end());
        build(arr, 0, 0, n - 1);
    }

    /*
     * countLess(L, R, x)
     * Public entry — [L,R] index range me kitne elements < x
     * Recursive call root se shuru: node=0, segment=[0, n-1]
     */
    int countLess(int L, int R, int x) const {
        if (n == 0 || L > R) return 0;
        return countLessRec(L, R, x, 0, 0, n - 1);
    }

    /*
     * countLessEqual(L, R, x)
     * Public entry — [L,R] me kitne elements <= x
     */
    int countLessEqual(int L, int R, int x) const {
        if (n == 0 || L > R) return 0;
        return countLessEqualRec(L, R, x, 0, 0, n - 1);
    }

    /*
     * countInRange(L, R, A, B)
     * --------------------------
     * Do alag ranges:
     *   INDEX [L,R] — array ke kaunse positions
     *   VALUE [A,B] — element ki value kahan honi chahiye (inclusive)
     *
     * Formula: count(<=B) - count(<A) = count in [A,B]
     *
     * Example: arr=[5,1,2,3,4], L=1,R=4, A=2,B=4
     *   values at 1..4 = {1,2,3,4}
     *   [2,4] me {2,3,4} → 3 elements
     */
    int countInRange(int L, int R, int A, int B) const {
        return countLessEqual(L, R, B) - countLess(L, R, A);
    }

    /*
     * kthSmallest(L, R, k)
     * --------------------
     * [L,R] me k-th smallest VALUE dhundho (k=1-indexed).
     *
     * GALAT tarika: tree walk karke k-th element — unsorted array pe fail
     * SAHI tarika: Binary Search on VALUE
     *
     *   lo = min value, hi = max value
     *   jab tak lo < hi:
     *     mid = (lo+hi)/2
     *     agar [L,R] me <= mid wale elements >= k → answer left (hi=mid)
     *     warna → answer right (lo=mid+1)
     *
     * Example: arr=[5,1,2,3,4], L=0,R=4,k=3
     *   sorted = {1,2,3,4,5} → 3rd smallest = 3
     */
    int kthSmallest(int L, int R, int k) const {
        int lo = loVal, hi = hiVal;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (countLessEqual(L, R, mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }
};

/*
 * main() — template demo
 * Teen alag queries test karta hai: kth, countLess, countInRange
 */
int main() {
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";

    cout << "kthSmallest [0,4] k=3 -> " << mst.kthSmallest(0, 4, 3) << "\n";
    cout << "countLess [0,4] x=3   -> " << mst.countLess(0, 4, 3) << "\n";
    cout << "countInRange [1,4] [2,4] -> " << mst.countInRange(1, 4, 2, 4) << "\n";

    return 0;
}
