/*
 * ============================================================================
 * TOPIC    : Grid DP
 * FILE     : grid_min_path_sum.cpp
 * PROBLEM  : Minimum path sum from top-left to bottom-right
 * APPROACH : dp[i][j] = grid[i][j] + min(top, left)
 * COMPLEX  : Time: O(m * n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int minPathSum(vector<vector<int>> grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    dp[0] = grid[0][0];

    for (int j = 1; j < n; j++)
        dp[j] = dp[j - 1] + grid[0][j];

    for (int i = 1; i < m; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < n; j++)
            dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
    }

    return dp[n - 1];
}

int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << "Minimum path sum = " << minPathSum(grid) << endl;
    return 0;
}
