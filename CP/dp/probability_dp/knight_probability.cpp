/*
 * ============================================================================
 * TOPIC    : Probability DP
 * FILE     : knight_probability.cpp
 * PROBLEM  : Knight stays on board after K moves (LeetCode 688 style)
 * APPROACH : dp[move][i][j] = probability at cell (i,j) after move steps
 * COMPLEX  : Time: O(K * n^2)  |  Space: O(n^2)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

double knightProbability(int n, int k, int row, int col) {
    const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    vector<vector<double>> dp(n, vector<double>(n, 0.0)), ndp(n, vector<double>(n, 0.0));
    dp[row][col] = 1.0;

    for (int move = 0; move < k; move++) {
        for (int i = 0; i < n; i++)
            fill(ndp[i].begin(), ndp[i].end(), 0.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == 0)
                    continue;
                for (int d = 0; d < 8; d++) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n)
                        ndp[ni][nj] += dp[i][j] / 8.0;
                }
            }
        }
        dp.swap(ndp);
    }

    double ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += dp[i][j];
    return ans;
}

int main() {
    int n = 3, k = 2, row = 0, col = 0;
    cout << fixed << setprecision(6);
    cout << "Knight probability on " << n << "x" << n << " after " << k
         << " moves = " << knightProbability(n, k, row, col) << endl;
    return 0;
}
