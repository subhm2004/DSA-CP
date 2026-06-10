/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Maximum Product Subarray
 * FILE     : max_product_subarray.cpp
 * PROBLEM  : Largest product of contiguous subarray
 * LEETCODE : 152 — Maximum Product Subarray
 * APPROACH : Track maxProd and minProd (negative flip)
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MAX PRODUCT SUBARRAY — contiguous subarray ka sabse bada product
// ────────────────────────────────────────────────────────────────────────────
// Negative number se max aur min swap ho jata hai — chhota negative * negative = bada positive.
// Isliye har step pe curMax (best ending here) aur curMin (worst ending) dono track karo.
// Har element pe: extend purani subarray ya nayi subarray start karo.
// best = sabse zyada curMax jo kabhi dekha.
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── maxProduct: max contiguous subarray product return karo ────────────────
//   1) best, curMax, curMin = nums[0] se initialize
//   2) Negative aaye to curMax/curMin swap — sign flip effect handle
//   3) curMax = max(nums[i], curMax*nums[i]) — extend ya restart
//   4) curMin = min(nums[i], curMin*nums[i]) — negative chain ke liye
//   5) best = max(best, curMax) — global maximum update
int maxProduct(const vector<int> &nums) {
    int best = nums[0], curMax = nums[0], curMin = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] < 0) swap(curMax, curMin);              // negative se max-min flip
        curMax = max(nums[i], curMax * nums[i]);             // ending here ka best product
        curMin = min(nums[i], curMin * nums[i]);             // ending here ka worst (neg chain)
        best = max(best, curMax);                            // overall answer update
    }
    return best;
}

// ── main: sample array pe max product test ─────────────────────────────────
//   1) nums = {2,3,-2,4} — best subarray [2,3] product = 6
//   2) Answer print karo
int main() {
    vector<int> nums = {2, 3, -2, 4};
    cout << maxProduct(nums) << endl; // 6
    return 0;
}
