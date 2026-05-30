/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Minimum Path Sum (Grid)
 * FILE     : minimum_path_sum_grid.cpp
 * PROBLEM  : Min sum path top-left to bottom-right
 * LEETCODE : 64 — Minimum Path Sum
 * APPROACH : dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
 * COMPLEX  : Time: O(n*m)  |  Space: O(m) optimized
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int minPathSum(const vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> dp(m);
    dp[0] = grid[0][0];
    for (int j = 1; j < m; j++) dp[j] = dp[j - 1] + grid[0][j];
    for (int i = 1; i < n; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < m; j++)
            dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
    }
    return dp[m - 1];
}

int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSum(grid) << endl; // 7
    return 0;
}
