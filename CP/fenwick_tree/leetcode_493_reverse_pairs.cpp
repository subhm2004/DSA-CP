#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LEETCODE 493 — Reverse Pairs
 * ════════════════════════════════════════════════════════════════════════════
 *
 * DIYA HAI:
 *   nums array.
 *
 * POOCHNA HAI:
 *   Kitne pairs (i, j) jahan i < j aur nums[i] > 2 * nums[j]?
 *
 * Example: nums = [1, 3, 2, 3, 1]  →  answer = 2
 *   Valid: (1,4) → 3>2, (3,4) → 3>2
 *
 * NAIVE: double loop → O(n²)
 *
 * APPROACH: Coordinate_Compression_LL + Fenwick Tree
 *   LEFT → RIGHT scan:
 *     BIT me nums[0..j-1] ki frequencies hain.
 *     nums[i] > 2*nums[j]  ⟺  BIT me kitne values > 2*nums[j]?
 *                        = seen - count(≤ 2*nums[j])
 *
 *   Compression pool: nums[i] aur 2*nums[i] dono (long long overflow avoid).
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
     * Frequency BIT — 1-indexed, size = unique compressed values.
     */
    FenwickTree(int n_) : n(n_), bit(n_ + 1, 0) {}

    /*
     * add(i, delta)
     * Value ki compressed index i pe frequency +delta.
     * i & -i trick se O(log n) update.
     */
    void add(int i, int delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    /*
     * prefixSum(i)
     * [1..i] total frequency — compressed ranks 0..i-1 ke elements count.
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
     * reversePairs(nums)
     * ------------------
     *
     * Step 1 — Compression pool banao:
     *   Har nums[i] aur 2*nums[i] pool me (LL class — overflow safe).
     *
     * Step 2 — LEFT → RIGHT (j = 0 .. n-1):
     *   Pehle QUERY (i < j wale already BIT me):
     *     threshold = 2 * nums[j]
     *     seen       = prefixSum(size)           → total elements in BIT
     *     notGreater = prefixSum(upper_bit_id(threshold))  → ≤ threshold
     *     pairs     += seen - notGreater         → strictly greater count
     *
     *   Phir UPDATE:
     *     bit.add(bit_id(nums[j]), 1)  → nums[j] ko BIT me daalo
     *
     * Kyun ≤ threshold?
     *   nums[i] > 2*nums[j] means nums[i] STRICTLY greater than threshold.
     *   count(≤ threshold) ko minus karke > wale milte hain.
     *
     * Example [1,3,2,3,1], j=4, threshold=2:
     *   BIT={1,3,2,3}, seen=4, countLE(2)=2 (values 1,2)
     *   pairs += 4-2 = 2  → (1,4) aur (3,4)
     */
    int reversePairs(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 0) return 0;

        vector<long long> pool;
        for (int x : nums) {
            pool.push_back(x);
            pool.push_back(2LL * x);
        }
        Coordinate_Compression_LL cc(pool);
        FenwickTree bit(cc.size());

        long long pairs = 0;

        for (int j = 0; j < n; ++j) {
            long long threshold = 2LL * nums[j];
            int seen = bit.prefixSum(cc.size());
            int notGreater = bit.prefixSum(cc.upper_bit_id(threshold));
            pairs += seen - notGreater;
            bit.add(cc.bit_id(nums[j]), 1);
        }

        return (int)pairs;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> nums1 = {1, 3, 2, 3, 1};
    cout << "LC 493: [1, 3, 2, 3, 1]\n";
    cout << "  reverse pairs = " << sol.reversePairs(nums1) << " (expected 2)\n\n";

    vector<int> nums2 = {2, 4, 3, 5, 1};
    cout << "LC 493: [2, 4, 3, 5, 1]\n";
    cout << "  reverse pairs = " << sol.reversePairs(nums2) << " (expected 3)\n\n";

    vector<int> nums3 = {-5, -5};
    cout << "LC 493: [-5, -5]\n";
    cout << "  reverse pairs = " << sol.reversePairs(nums3) << " (1 pair)\n\n";

    vector<int> nums4 = {5, 4, 3, 2, 1};
    cout << "LC 493: [5, 4, 3, 2, 1]\n";
    cout << "  reverse pairs = " << sol.reversePairs(nums4) << "\n";

    return 0;
}
