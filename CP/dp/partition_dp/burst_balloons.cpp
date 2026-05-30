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

int main() {
    vector<int> nums = {3, 1, 5, 8};
    cout << "Max coins (burst balloons) = " << maxCoins(nums) << endl;
    return 0;
}
