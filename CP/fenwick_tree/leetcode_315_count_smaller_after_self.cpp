#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LEETCODE 315 — Count of Smaller Numbers After Self
 * ════════════════════════════════════════════════════════════════════════════
 *
 * DIYA HAI:
 *   nums array (duplicates ho sakte hain).
 *
 * POOCHNA HAI:
 *   ans[i] = index i ke RIGHT me kitne elements nums[i] se CHHOTE hain?
 *
 * Example: nums = [5, 2, 6, 1]  →  [2, 1, 1, 0]
 *
 * NAIVE: har i ke liye right scan → O(n²)
 *
 * APPROACH: Coordinate_Compression + Fenwick Tree
 *   RIGHT → LEFT scan:
 *     BIT me sirf i ke RIGHT wale elements ki frequency hoti hai.
 *     ans[i] = BIT me kitne elements < nums[i]?
 *     phir nums[i] ko BIT me +1 daalo.
 *
 * Time: O(n log n)  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class FenwickTree {
private:
    int n;
    vector<int> bit;  // 1-indexed frequency BIT

public:
    /*
     * FenwickTree(n)
     * -------------
     * n = kitne unique compressed values hain (Coordinate_Compression::size()).
     * bit size n+1 — index 0 dummy, actual use 1..n.
     */
    FenwickTree(int n_) : n(n_), bit(n_ + 1, 0) {}

    /*
     * add(i, delta)
     * -------------
     * Compressed index i (1-indexed) pe frequency badhao.
     *
     * i & -i = lowest set bit → agla parent node jahan ye index contribute karta hai.
     * Loop i <= n tak — O(log n).
     *
     * Example: i=2 pe +1 → bit[2]++, phir i=4, bit[4]++ ...
     */
    void add(int i, int delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    /*
     * prefixSum(i)
     * ------------
     * [1..i] ki total frequency — matlab compressed id 0 se i-1 wale
     * kitne elements BIT me daale ja chuke hain.
     *
     * i -= i & -i se neeche wale responsible nodes add karte hain — O(log n).
     *
     * LC 315 me: prefixSum(id) = right side me kitne elements current se CHHOTE.
     *   id = compress[nums[i]] → values with compressed rank < id are smaller.
     */
    int prefixSum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }
};

class Solution {
public:
    /*
     * countSmaller(nums)
     * ------------------
     * Main solver — har index ke liye right me smaller count.
     *
     * Step 1: Coordinate_Compression cc(nums)
     *         Badi values → 0,1,2,... chhote ids (BIT size kam)
     *
     * Step 2: RIGHT se LEFT loop (i = n-1 .. 0)
     *         Kyun right se? BIT me sirf "abhi tak process hue" = RIGHT wale elements
     *
     * Step 3: Har i pe:
     *           id  = cc.compress[nums[i]]     → is value ki rank
     *           ans[i] = bit.prefixSum(id)    → id se chhote kitne already in BIT
     *           bit.add(cc.bit_id(nums[i]), 1) → current element BIT me daalo
     *
     * Walkthrough [5,2,6,1], compressed: 1→0, 2→1, 5→2, 6→3
     *   i=3, val=1: BIT empty        → ans[3]=0, add bit[1]
     *   i=2, val=6: prefixSum(3)=1   → ans[2]=1, add bit[4]
     *   i=1, val=2: prefixSum(1)=1   → ans[1]=1, add bit[2]
     *   i=0, val=5: prefixSum(2)=2   → ans[0]=2
     */
    vector<int> countSmaller(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 0) return {};

        Coordinate_Compression cc(nums);
        FenwickTree bit(cc.size());
        vector<int> ans(n, 0);

        for (int i = n - 1; i >= 0; --i) {
            int id = cc.compress[nums[i]];
            ans[i] = bit.prefixSum(id);
            bit.add(cc.bit_id(nums[i]), 1);
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums1 = {5, 2, 6, 1};
    cout << "LC 315: [5, 2, 6, 1]\n  ans = ";
    for (int x : sol.countSmaller(nums1)) cout << x << " ";
    cout << " (expected 2 1 1 0)\n\n";

    vector<int> nums2 = {-1};
    cout << "LC 315: [-1]\n  ans = ";
    for (int x : sol.countSmaller(nums2)) cout << x << " ";
    cout << " (expected 0)\n\n";

    vector<int> nums3 = {-1, -1};
    cout << "LC 315: [-1, -1]\n  ans = ";
    for (int x : sol.countSmaller(nums3)) cout << x << " ";
    cout << " (expected 0 0)\n\n";

    vector<int> nums4 = {3, 1, 2, 3, 1};
    cout << "LC 315: [3, 1, 2, 3, 1]\n  ans = ";
    for (int x : sol.countSmaller(nums4)) cout << x << " ";
    cout << "\n";

    return 0;
}
