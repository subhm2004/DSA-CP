#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * PROBLEM: Count Triplet Inversions
 * ════════════════════════════════════════════════════════════════════════════
 *
 * Triplet inversion = teen indices (i, j, k) jahan:
 *   i < j < k   (order left to right)
 *   arr[i] > arr[j] > arr[k]   (values decreasing)
 *
 * Matlab: beech wale j ke LEFT me bada element, RIGHT me chhota element
 *
 * Example: arr = [3, 2, 1]
 *   i=0, j=1, k=2 → 3 > 2 > 1 ✓ → 1 triplet
 *
 * Example: arr = [4, 3, 2, 1]
 *   (0,1,2): 4>3>2, (0,1,3): 4>3>1, (0,2,3): 4>2>1, (1,2,3): 3>2>1
 *   Total = 4 triplets
 *
 * Example: arr = [5, 1, 2, 3, 4]
 *   koi bhi triplet nahi jahan middle se left bada aur right chhota ho
 *   Total = 0
 *
 * KEY INSIGHT (middle element j fix karo):
 *   left  = [0..j-1] me kitne > arr[j] ?
 *   right = [j+1..n-1] me kitne < arr[j] ?
 *   har left choice + har right choice = ek triplet
 *   contribution at j = left × right
 *
 * APPROACH: Merge Sort Tree
 *   left  = (j) - countLessEqual(0, j-1, arr[j])
 *   right = countLess(j+1, n-1, arr[j])
 *
 * Range version [L,R]:
 *   j from L+1 to R-1, left in [L,j-1], right in [j+1,R]
 *
 * Time: O(n log² n) full array | O((R-L) log² n) per range query
 * ════════════════════════════════════════════════════════════════════════════
 */

class MergeSortTree {
private:
    int n;
    vector<int> arr;
    vector<vector<int>> tree;

    /*
     * build(node, l, r)
     * Har node = us segment ka sorted vector
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
     * countLess(ql, qr, x, node, l, r)
     * [ql..qr] me STRICTLY < x wale elements
     * RIGHT side ke liye: kitne arr[k] < arr[j]
     */
    int countLess(int ql, int qr, int x, int node, int l, int r) const {
        if (ql > qr || r < ql || l > qr) return 0;
        if (ql <= l && r <= qr)
            return (int)(lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin());
        int mid = (l + r) / 2;
        return countLess(ql, qr, x, 2 * node + 1, l, mid)
             + countLess(ql, qr, x, 2 * node + 2, mid + 1, r);
    }

    /*
     * countLessEqual(ql, qr, x, node, l, r)
     * [ql..qr] me <= x wale elements
     * LEFT side se > arr[j] nikalne ke liye: leftSize - countLessEqual
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
     * tripletInversionCount()
     * -----------------------
     * Poori array me triplet inversions count.
     *
     * Har j = 1 se n-2 (middle index):
     *   leftGreater  = [0,j-1] me > arr[j]
     *                = j - countLessEqual(0, j-1, arr[j])
     *   rightSmaller = [j+1,n-1] me < arr[j]
     *                = countLess(j+1, n-1, arr[j])
     *   ans += leftGreater * rightSmaller
     *
     * Walkthrough arr=[3,2,1], j=1, arr[j]=2:
     *   left: [3]>2 → 1, right: [1]<2 → 1 → add 1 ✓
     */
    long long tripletInversionCount() const {
        if (n < 3) return 0;
        long long ans = 0;
        for (int j = 1; j <= n - 2; ++j) {
            int leftGreater = j - countLessEqual(0, j - 1, arr[j], 0, 0, n - 1);
            int rightSmaller = countLess(j + 1, n - 1, arr[j], 0, 0, n - 1);
            ans += 1LL * leftGreater * rightSmaller;
        }
        return ans;
    }

    /*
     * tripletInversionCountInRange(L, R)
     * ----------------------------------
     * Sirf [L..R] ke andar triplet inversions.
     * L <= i < j < k <= R aur arr[i] > arr[j] > arr[k]
     *
     * Har j = L+1 se R-1:
     *   leftGreater  = [L,j-1] me > arr[j] = (j-L) - countLE(L,j-1,arr[j])
     *   rightSmaller = [j+1,R] me < arr[j] = countLess(j+1,R,arr[j])
     *
     * Example arr=[4,3,2,1], L=0,R=3:
     *   j=1: left=1, right=2 → 2
     *   j=2: left=2, right=1 → 2
     *   total = 4 ✓
     */
    long long tripletInversionCountInRange(int L, int R) const {
        if (R - L + 1 < 3) return 0;
        long long ans = 0;
        for (int j = L + 1; j <= R - 1; ++j) {
            int leftSize = j - L;
            int leftGreater = leftSize - countLessEqual(L, j - 1, arr[j], 0, 0, n - 1);
            int rightSmaller = countLess(j + 1, R, arr[j], 0, 0, n - 1);
            ans += 1LL * leftGreater * rightSmaller;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example 1
    vector<int> arr = {4, 3, 2, 1};
    MergeSortTree mst(arr);
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTriplet inversions (full) -> " << mst.tripletInversionCount() << "\n";

    // Example 2
    vector<int> arr2 = {5, 1, 2, 3, 4};
    MergeSortTree mst2(arr2);
    cout << "\nArray: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nTriplet inversions (full) -> " << mst2.tripletInversionCount() << "\n";

    // Example 3 — range queries
    vector<int> arr3 = {3, 2, 1, 4, 0};
    MergeSortTree mst3(arr3);
    cout << "\nArray: ";
    for (int i = 0; i < (int)arr3.size(); ++i)
        cout << "[" << i << "]=" << arr3[i] << " ";
    cout << "\nTriplet inversions (full) -> " << mst3.tripletInversionCount() << "\n";

    vector<pair<int, int>> queries = {{0, 2}, {0, 4}, {2, 4}};
    cout << "\n-- Range triplet inversion queries --\n";
    for (auto& [L, R] : queries)
        cout << "(" << L << "," << R << ") -> "
             << mst3.tripletInversionCountInRange(L, R) << "\n";

    return 0;
}
