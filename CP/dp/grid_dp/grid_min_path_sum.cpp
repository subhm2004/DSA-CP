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

// ════════════════════════════════════════════════════════════════════════════
// GRID MINIMUM PATH SUM — Weighted Grid DP
// ────────────────────────────────────────────────────────────────────────────
// Top-left se bottom-right — sirf right/down; har cell ka cost add hota hai.
// dp[j] = current row me column j tak pohonchne ka minimum path sum.
// Transition: dp[j] = grid[i][j] + min(dp[j] upar se, dp[j-1] left se).
// Pehli row/col prefix sum se initialize — sirf ek direction se aana possible.
// ════════════════════════════════════════════════════════════════════════════

// ── minPathSum: top-left se bottom-right minimum cost path ────────────────
//   1) dp[0] = grid[0][0]; pehli row: dp[j] = dp[j-1] + grid[0][j] (sirf right)
//   2) har row i>=1: dp[0] += grid[i][0] — first col sirf down se aata hai
//   3) dp[j] = grid[i][j] + min(dp[j], dp[j-1]) — up vs left me se sasta choose
//   4) dp array ek row hold karta hai — O(n) space, poora grid scan O(m*n)
//   5) dp[n-1] return — bottom-right tak minimum total path sum
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

// ── main: sample 3x3 grid par min path sum print ──────────────────────────
//   {{1,3,1},{1,5,1},{4,2,1}} — expected sum 7 stdout par
int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << "Minimum path sum = " << minPathSum(grid) << endl;
    return 0;
}
