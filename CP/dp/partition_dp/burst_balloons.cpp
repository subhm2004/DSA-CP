/*
 * ============================================================================
 * TOPIC    : Partition DP
 * FILE     : burst_balloons.cpp
 * PROBLEM  : Burst balloons to maximize coins — nums[i] on burst
 * APPROACH : Partition DP — try last balloon k in interval (i,j)
 * COMPLEX  : Time: O(n^3)  |  Space: O(n^2)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BURST BALLOONS — Partition / Interval DP (LeetCode 312)
// ────────────────────────────────────────────────────────────────────────────
// Boundary me 1 insert karo — edge balloons virtual hain, burst nahi hote.
// dp[i][j] = open interval (i,j) ke andar balloons burst karke max coins.
// Har step me k = LAST balloon burst karo (i < k < j) — order matter karta hai.
// Coins = nums[i]*nums[k]*nums[j] + dp[i][k] + dp[k][j]; len 3 se n tak fill.
// ════════════════════════════════════════════════════════════════════════════

// ── maxCoins: burst balloons se maximum coins ─────────────────────────────
//   1) nums ke start/end me 1 push — boundary neighbors har burst me use honge
//   2) dp[i][j] = coins from bursting all balloons strictly between i aur j
//   3) len 3 se badhao — har (i,j) interval ke liye k = last burst try karo
//   4) transition: dp[i][j] = max(dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j])
//   5) dp[0][n-1] return — poori array ke andar sab balloons burst karke max
int maxCoins(vector<int> nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 3; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = max(dp[i][j],
                               dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
            }
        }
    }
    return dp[0][n - 1];
}

// ── main: sample balloons par max coins print ─────────────────────────────
//   {3,1,5,8} input — expected max coins stdout par dikhao
int main() {
    vector<int> nums = {3, 1, 5, 8};
    cout << "Max coins (burst balloons) = " << maxCoins(nums) << endl;
    return 0;
}
