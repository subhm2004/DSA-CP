#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Range Median
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Diya hai:
 *   - Array size n
 *   - Queries (L, R) — index range
 *
 * Poochna hai:
 *   - [L..R] ke elements ka MEDIAN (beech wala value) kya hai?
 *
 * Median rules:
 *   ODD length  → ek median:  sorted list ka middle element
 *   EVEN length → do median:  lower middle aur upper middle
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *
 *   Query (0, 4): values {5,1,2,3,4} → sorted {1,2,3,4,5}
 *     len=5 (odd) → median = 3 (3rd smallest)
 *
 *   Query (1, 4): values {1,2,3,4} → sorted same
 *     len=4 (even) → lower=2, upper=3
 *
 * APPROACH: Median = special case of kthSmallest
 *   odd:  k = (len+1)/2
 *   even: k = len/2 aur len/2+1
 *
 * Time: O(log² n) per query
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n, loVal, hiVal;
    vector<vector<int>> tree;

    /*
     * build(arr, node, l, r)
     * Merge sort tree — har node sorted vector
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
     * kthSmallest ke binary search me use — [ql,qr] me <= x count
     */
    int countLessEqual(int ql, int qr, int x, int node, int l, int r) const {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());
        int mid = (l + r) / 2;
        return countLessEqual(ql, qr, x, 2 * node + 1, l, mid)
             + countLessEqual(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

    /*
     * kthSmallest(L, R, k) — private helper
     * Binary search on value space:
     *   sabse chhota v jahan [L,R] me <= v wale >= k elements
     */
    int kthSmallest(int L, int R, int k) const {
        int lo = loVal, hi = hiVal;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (countLessEqual(L, R, mid, 0, 0, n - 1) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

public:
    /*
     * Constructor — tree build + min/max for BS
     */
    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, {});
        loVal = *min_element(arr.begin(), arr.end());
        hiVal = *max_element(arr.begin(), arr.end());
        build(arr, 0, 0, n - 1);
    }

    /*
     * median(L, R)
     * ------------
     * Odd length range ka single median.
     *
     *   len = R - L + 1
     *   median position (1-indexed sorted me) = (len+1)/2
     *
     * Example: len=5 → k=3 → 3rd smallest
     *   [5,1,2,3,4] sorted {1,2,3,4,5} → median = 3
     */
    int median(int L, int R) const {
        int len = R - L + 1;
        return kthSmallest(L, R, (len + 1) / 2);
    }

    /*
     * medianPair(L, R)
     * ----------------
     * Odd len  → dono same {median, median}
     * Even len → {lower median, upper median}
     *
     *   even: k1 = len/2,     k2 = len/2 + 1
     *   Example len=4: k1=2 (2nd smallest), k2=3 (3rd smallest)
     *   {1,2,3,4} → lower=2, upper=3
     */
    pair<int,int> medianPair(int L, int R) const {
        int len = R - L + 1;
        if (len % 2 == 1)
            return {median(L, R), median(L, R)};
        return {kthSmallest(L, R, len / 2), kthSmallest(L, R, len / 2 + 1)};
    }
};

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};
    MergeSortTree mst(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";

    auto [lo, hi] = mst.medianPair(0, 4);
    cout << "median [0,4] (odd len=5)  -> " << lo << "\n";

    tie(lo, hi) = mst.medianPair(1, 4);
    cout << "median [1,4] (even len=4) -> lower=" << lo << " upper=" << hi << "\n";

    tie(lo, hi) = mst.medianPair(0, 2);
    cout << "median [0,2] (odd len=3)  -> " << lo << "\n";

    return 0;
}
