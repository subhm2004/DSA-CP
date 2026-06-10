/*
 * ============================================================================
 * TOPIC    : Two Pointers — Two Sum II (Sorted Array)
 * FILE     : two_sum_sorted.cpp
 * PROBLEM  : 1-indexed pair summing to target in sorted array
 * LEETCODE : 167 — Two Sum II
 * APPROACH : Two pointers from both ends
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO SUM II (SORTED) — End se do pointers milao
// ────────────────────────────────────────────────────────────────────────────
// Array sorted hai — hash map ki zaroorat nahi
// sum == target -> pair mil gaya (1-indexed return)
// sum < target -> chahiye bada number -> l++
// sum > target -> chahiye chhota -> r--
// O(n) time, O(1) space
// ════════════════════════════════════════════════════════════════════════════

// ── twoSumSorted: 1-indexed indices jinka sum target ───────────────────────
//   1) l=0, r=n-1
//   2) sum = nums[l]+nums[r]
//   3) sum==target -> {l+1, r+1} return
//   4) sum<target -> l++, warna r--
vector<int> twoSumSorted(vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum == target) return {l + 1, r + 1}; // 1-indexed
        if (sum < target) l++;
        else r--;
    }
    return {};
}

// ── main: {2,7,11,15}, target=9 -> 1 2 ─────────────────────────────────────
int main() {
    vector<int> nums = {2, 7, 11, 15};
    auto ans = twoSumSorted(nums, 9);
    cout << ans[0] << " " << ans[1] << endl; // 1 2
    return 0;
}
