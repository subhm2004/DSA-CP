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

// ════════════════════════════════════════════════════════════════════════════
// UNIQUE PATHS — grid me (0,0) se (m-1,n-1) tak sirf right/down moves
// ────────────────────────────────────────────────────────────────────────────
// Cell (i,j) tak paths = upar se aane ke paths + left se aane ke paths.
// First row/col me sirf 1 path (seedha line me jao).
// 1D dp array — har row process karte waqt purani row overwrite, space O(n).
// COMPLEX: Time O(m*n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── uniquePaths: m x n grid me unique paths count ──────────────────────────
//   1) dp[j] = current row me column j tak paths count
//   2) Pehli row sab 1 — sirf right moves se ek hi path
//   3) Har nayi row: dp[0] stays 1 (sirf down), dp[j] += dp[j-1]
//   4) dp[j] += dp[j-1] means paths from up (old dp[j]) + left (dp[j-1])
//   5) dp[n-1] = bottom-right cell tak total paths
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);                                  // first row — sab 1 path
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[j] += dp[j - 1];                            // upar + left se paths add
    return dp[n - 1];
}

// ── main: 3x7 grid pe unique paths test ────────────────────────────────────
//   1) uniquePaths(3,7) call — expected 28 (C(8,2) combinatorics)
//   2) Answer print karo
int main() {
    cout << uniquePaths(3, 7) << endl; // 28
    return 0;
}
