#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LEETCODE 327 — Count of Range Sum
 * ════════════════════════════════════════════════════════════════════════════
 *
 * DIYA HAI:
 *   nums array, lower aur upper bounds.
 *
 * POOCHNA HAI:
 *   Kitni subarrays [i,j] jinki sum ∈ [lower, upper]?
 *
 * Example: nums=[-2,5,-1], lower=-2, upper=2  →  answer = 3
 *
 * KEY — Prefix sum transform:
 *   sum(i..j) = pref[j+1] - pref[i]
 *   lower ≤ pref[j+1] - pref[i] ≤ upper
 *   ⟺  pref[j+1]-upper ≤ pref[i] ≤ pref[j+1]-lower
 *
 *   Har end point k fix karo → kitne start prefix satisfy karte hain?
 *
 * APPROACH: Coordinate_Compression_LL + Fenwick Tree
 *   Left → right: pehle query BIT, phir current prefix add.
 *
 * Time: O(n log n)  |  Space: O(n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class FenwickTree {
private:
    int n;
    vector<int> bit;

public:
    /*
     * FenwickTree(n)
     * n = compressed coordinate range (unique prefix-related values).
     */
    FenwickTree(int n_) : n(n_), bit(n_ + 1, 0) {}

    /*
     * add(i, delta)
     * Prefix sum value ki frequency BIT me badhao (1-indexed i).
     */
    void add(int i, int delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    /*
     * prefixSum(i)
     * [1..i] compressed indices ki total frequency.
     */
    int prefixSum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    /*
     * rangeSum(l, r)
     * ----------------
     * Compressed range [l,r] me kitni prefix sums pehle se dekhi hain.
     * Inclusion-exclusion: prefixSum(r) - prefixSum(l-1).
     *
     * LC 327 me: kitne purane pref[i] ∈ [curr-upper, curr-lower] hain.
     */
    int rangeSum(int l, int r) const {
        if (l > r) return 0;
        return prefixSum(r) - prefixSum(l - 1);
    }
};

class Solution {
public:
    /*
     * countRangeSum(nums, lower, upper)
     * --------------------------------
     *
     * Step 1 — Prefix sums:
     *   pref[0]=0, pref[k]=nums[0]+...+nums[k-1]
     *
     * Step 2 — Compression pool:
     *   Saare pref values + har pref ke (pref-upper) aur (pref-lower)
     *   Query boundaries bhi compress honi chahiye → pool me daalo.
     *   Coordinate_Compression_LL use (prefix long long ho sakte hain).
     *
     * Step 3 — BIT me pref[0]=0 daalo (empty prefix valid hai).
     *
     * Step 4 — k = 1 se n:
     *   curr = pref[k]
     *   lo = curr - upper,  hi = curr - lower
     *   ans += BIT.rangeSum(lo, hi)   ← kitne purane prefix is range me
     *   BIT.add(curr)                 ← ab curr ko future ke liye store karo
     *
     * Example [-2,5,-1]: pref=[0,-2,3,2]
     *   k=1, curr=-2: lo=-4, hi=0  → count pref[0]=0 in range → +1
     *   k=2, curr=3:  lo=1, hi=5   → count pref in [1,5] → ...
     */
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = (int)nums.size();
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i)
            pref[i + 1] = pref[i] + nums[i];

        vector<long long> pool = pref;
        for (long long p : pref) {
            pool.push_back(p - upper);
            pool.push_back(p - lower);
        }

        Coordinate_Compression_LL cc(pool);
        FenwickTree bit(cc.size());
        long long ans = 0;

        bit.add(cc.bit_id(pref[0]), 1);

        for (int k = 1; k <= n; ++k) {
            long long curr = pref[k];
            long long lo = curr - upper;
            long long hi = curr - lower;

            ans += bit.rangeSum(cc.lower_bit_id(lo), cc.upper_bit_id(hi));
            bit.add(cc.bit_id(curr), 1);
        }

        return (int)ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums1 = {-2, 5, -1};
    cout << "LC 327: [-2,5,-1], lower=-2, upper=2\n";
    cout << "  Answer = " << sol.countRangeSum(nums1, -2, 2) << " (expected 3)\n\n";

    vector<int> nums2 = {0};
    cout << "LC 327: [0], lower=0, upper=0\n";
    cout << "  Answer = " << sol.countRangeSum(nums2, 0, 0) << " (expected 1)\n\n";

    vector<int> nums3 = {-2, 5, -1, 5, 2, -2};
    cout << "LC 327: [-2,5,-1,5,2,-2], lower=-2, upper=2\n";
    cout << "  Answer = " << sol.countRangeSum(nums3, -2, 2) << "\n";

    return 0;
}
