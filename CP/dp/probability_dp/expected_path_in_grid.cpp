/*
 * ============================================================================
 * TOPIC    : Probability DP
 * FILE     : expected_path_in_grid.cpp
 * PROBLEM  : Probability to reach bottom-right from top-left (right/down only)
 * APPROACH : dp[i][j] = probability at cell, move with prob 0.5 each direction
 * COMPLEX  : Time: O(m * n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

double reachBottomRight(int m, int n) {
    vector<double> dp(n, 0.0);
    dp[0] = 1.0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0)
                continue;
            double fromTop = (i > 0) ? dp[j] * 0.5 : 0.0;
            double fromLeft = (j > 0) ? dp[j - 1] * 0.5 : 0.0;
            dp[j] = fromTop + fromLeft;
        }
    }
    return dp[n - 1];
}

int main() {
    int m = 3, n = 3;
    cout << fixed << setprecision(6);
    cout << "Probability to reach (" << m - 1 << "," << n - 1 << ") in " << m << "x" << n
         << " grid = " << reachBottomRight(m, n) << endl;
    return 0;
}
