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

bool canPartition(const vector<int> &nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2) return false;
    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (int x : nums)
        for (int s = target; s >= x; s--)
            dp[s] = dp[s] || dp[s - x];
    return dp[target];
}

int main() {
    vector<int> nums = {1, 5, 11, 5};
    cout << (canPartition(nums) ? "YES" : "NO") << endl; // YES
    return 0;
}
