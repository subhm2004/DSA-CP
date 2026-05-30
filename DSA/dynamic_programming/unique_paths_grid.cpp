/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Unique Paths (Grid)
 * FILE     : unique_paths_grid.cpp
 * PROBLEM  : Paths from (0,0) to (m-1,n-1) moving right/down
 * LEETCODE : 62 — Unique Paths
 * APPROACH : dp[i][j] = dp[i-1][j] + dp[i][j-1]
 * COMPLEX  : Time: O(m*n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[j] += dp[j - 1];
    return dp[n - 1];
}

int main() {
    cout << uniquePaths(3, 7) << endl; // 28
    return 0;
}
