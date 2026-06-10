/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Partition Equal Subset Sum
 * FILE     : partition_equal_subset.cpp
 * PROBLEM  : Split array into two equal-sum subsets
 * LEETCODE : 416 — Partition Equal Subset Sum
 * APPROACH : 0/1 knapsack — can we make sum/2?
 * COMPLEX  : Time: O(n*sum)  |  Space: O(sum)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PARTITION EQUAL SUBSET — array ko do equal-sum subsets me tod sakte ho?
// ────────────────────────────────────────────────────────────────────────────
// Agar total sum odd hai to impossible — seedha false.
// Do equal parts chahiye matlab ek part ka sum = total/2 banana hai.
// Classic 0/1 knapsack: dp[s] = kya sum s ban sakta hai current items se?
// Reverse loop zaroori — same item do baar use na ho (0/1 property).
// COMPLEX: Time O(n * target)  |  Space O(target)
// ════════════════════════════════════════════════════════════════════════════

// ── canPartition: equal subset partition possible hai ya nahi ──────────────
//   1) Total sum nikalo — odd ho to seedha false (equal split impossible)
//   2) target = total/2 — yeh sum banana hai ek subset se
//   3) dp[0]=true — empty subset se sum 0 hamesha possible
//   4) Har number x: s = target se x tak reverse loop — dp[s] |= dp[s-x]
//   5) dp[target] true ho to YES — do equal parts ban gaye
bool canPartition(const vector<int> &nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;                         // odd sum — divide nahi ho sakta
    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;                                          // sum 0 hamesha achievable
    for (int x : nums)
        for (int s = target; s >= x; s--)                // reverse — ek item ek hi baar
            dp[s] = dp[s] || dp[s - x];                  // x lo ya mat lo
    return dp[target];
}

// ── main: sample array pe partition check ──────────────────────────────────
//   1) nums = {1,5,11,5} — total 22, target 11 achievable
//   2) YES/NO print karo
int main() {
    vector<int> nums = {1, 5, 11, 5};
    cout << (canPartition(nums) ? "YES" : "NO") << endl; // YES
    return 0;
}
