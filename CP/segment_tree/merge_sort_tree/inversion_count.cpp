#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Inversion Count
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Ek array size n
 *
 * Poochna hai:
 *   - Kitne pairs (i, j) hain jahan i < j  AUR  arr[i] > arr[j] ?
 *   - Matlab baayein se dekho — kitni baar bada element chhote ke pehle aata hai
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   i=0 (value 5): 5 > 1, 5 > 2, 5 > 3, 5 > 4 → 4 inversions
 *   i=1,2,3: koi inversion nahi
 *   Total = 4
 *
 * Example 2: arr = [2, 4, 1, 3, 5]
 *   (0,2): 2>1, (1,2): 4>1 → total 3 inversions
 *
 * APPROACH: Merge Sort Tree
 *   Har i ke liye: [0, i-1] me kitne > arr[i]?
 *   = i - countLessEqual(0, i-1, arr[i])
 *
 * Time: O(n log² n)
 * NOTE: Classic merge sort inversion O(n log n) — zyada fast, alag technique
 * SIMILAR: LC 315 | LC 493 Reverse Pairs
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * Poora array se merge sort tree banao — preprocessing
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
     * [ql..qr] me <= x wale elements count.
     * Inversion me left side [0,i-1] me <= arr[i] count karna hai.
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
     * Constructor — tree build karo (ek baar)
     */
    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * max(n, 1), {});
        if (n) build(arr, 0, 0, n - 1);
    }

    /*
     * inversionCount(arr)
     * -------------------
     * Har index i = 1 se n-1:
     *
     *   left side = indices [0, i-1], total i elements
     *   inversions at i = kitne left elements > arr[i]
     *                   = i - countLessEqual(0, i-1, arr[i])
     *
     * Walkthrough arr=[5,1,2,3,4]:
     *   i=1: arr[1]=1, left=[5], countLE=0, inv+=1-0=1 (5>1) ✓
     *   i=2: arr[2]=2, left=[5,1], countLE=1, inv+=2-1=1 (5>2) ✓
     *   i=3,4: koi nahi
     *   total = 4
     */
    long long inversionCount(const vector<int>& arr) const {
        long long inv = 0;
        for (int i = 0; i < n; ++i) {
            if (i == 0) continue;
            int leq = countLessEqual(0, i - 1, arr[i], 0, 0, n - 1);
            inv += i - leq;
        }
        return inv;
    }
};

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nInversion count -> " << mst.inversionCount(arr) << "\n";

    vector<int> arr2 = {2, 4, 1, 3, 5};
    MergeSortTree mst2(arr2);
    cout << "\nArray: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nInversion count -> " << mst2.inversionCount(arr2) << "\n";

    return 0;
}
