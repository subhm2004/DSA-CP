/*
 * ============================================================================
 * TOPIC    : Grid DP
 * FILE     : grid_unique_paths.cpp
 * PROBLEM  : Unique paths from top-left to bottom-right (only right/down)
 * APPROACH : dp[i][j] = dp[i-1][j] + dp[i][j-1]
 * COMPLEX  : Time: O(m * n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long uniquePaths(int m, int n) {
    vector<long long> dp(n, 1);

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++)
            dp[j] += dp[j - 1];
    }

    return dp[n - 1];
}

int main() {
    int m = 3, n = 7;
    cout << "Unique paths in " << m << "x" << n << " grid: " << uniquePaths(m, n) << endl;
    return 0;
}
