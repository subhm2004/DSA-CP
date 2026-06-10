/*
 * ============================================================================
 * TOPIC    : Arrays — Kadane's Algorithm
 * FILE     : kadanes_max_subarray.cpp
 * PROBLEM  : Maximum sum contiguous subarray
 * LEETCODE : 53 — Maximum Subarray
 * APPROACH : cur = max(x, cur+x); best = max(best, cur)
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KADANE'S ALGORITHM — maximum sum contiguous subarray
// ────────────────────────────────────────────────────────────────────────────
// Funda: har step pe decide karo — naya subarray shuru karein ya extend?
// cur = max(nums[i], cur + nums[i]) — negative sum chhod do
// best = max(best, cur) — global maximum track karo
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── maxSubArray: Kadane se max subarray sum ────────────────────────────────
//   1) cur = best = nums[0] se start
//   2) i=1 se end — cur update: extend ya fresh start
//   3) best = max(best, cur) har step pe
//   4) best return — yahi maximum sum hai
int maxSubArray(vector<int> &nums) {
    int cur = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        cur = max(nums[i], cur + nums[i]);
        best = max(best, cur);
    }
    return best;
}

// ── main: sample array pe Kadane demo ──────────────────────────────────────
//   1) nums vector banao
//   2) maxSubArray print — expected 6 for sample
int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl; // 6
    return 0;
}
