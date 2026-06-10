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

// ════════════════════════════════════════════════════════════════════════════
// MINIMUM PATH SUM — grid me top-left se bottom-right tak min cost path
// ────────────────────────────────────────────────────────────────────────────
// Har cell pe aane ka cost = us cell ka value + upar ya left se aane ka min cost.
// 1D DP array se space optimize — har row process karte waqt purani row overwrite.
// Pehli row/col sirf ek direction se aate hain, isliye prefix sum jaisa build.
// COMPLEX: Time O(n*m)  |  Space O(m)
// ════════════════════════════════════════════════════════════════════════════

// ── minPathSum: grid ka minimum path sum return karo ───────────────────────
//   1) dp[j] = row i tak (0,j) pe min path sum — 1D space optimization
//   2) Pehli row: sirf left se aate hain, dp[j] = dp[j-1] + grid[0][j]
//   3) Baaki rows: dp[0] += grid[i][0] (sirf upar se)
//   4) Har cell: dp[j] = grid[i][j] + min(upar=dp[j], left=dp[j-1])
//   5) Last cell dp[m-1] = answer
int minPathSum(const vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> dp(m);
    dp[0] = grid[0][0];                                    // start cell
    for (int j = 1; j < m; j++) dp[j] = dp[j - 1] + grid[0][j]; // pehli row — sirf right move
    for (int i = 1; i < n; i++) {
        dp[0] += grid[i][0];                               // first col — sirf down move
        for (int j = 1; j < m; j++)
            dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);    // upar ya left se min leke aage badho
    }
    return dp[m - 1];
}

// ── main: sample grid pe min path sum test ─────────────────────────────────
//   1) 3x3 grid define karo
//   2) minPathSum call karke answer print — expected 7
int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSum(grid) << endl; // 7
    return 0;
}
