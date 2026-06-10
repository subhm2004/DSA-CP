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

// ════════════════════════════════════════════════════════════════════════════
// GRID UNIQUE PATHS — Classic 2D → 1D Grid DP
// ────────────────────────────────────────────────────────────────────────────
// Top-left (0,0) se bottom-right (m-1,n-1) — sirf RIGHT ya DOWN move allowed.
// dp[j] = current row me column j tak pohonchne ke unique paths.
// Pehli row sab 1 (sirf right moves); baaki rows: dp[j] += dp[j-1] (up + left).
// Space O(n) — ek row ka DP previous row se derive hota hai.
// ════════════════════════════════════════════════════════════════════════════

// ── uniquePaths: m x n grid me unique paths count ─────────────────────────
//   1) dp[j] = 1 for all j — pehli row me sirf right se pohonch sakte ho
//   2) har row i = 1..m-1 ke liye columns process karo
//   3) dp[j] += dp[j-1] — upar se (same col) + left se (prev col) paths jodo
//   4) dp[0] row me 1 hi rehta — first col me sirf down moves possible
//   5) dp[n-1] return — bottom-right cell tak total unique paths
long long uniquePaths(int m, int n) {
    vector<long long> dp(n, 1);

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++)
            dp[j] += dp[j - 1];
    }

    return dp[n - 1];
}

// ── main: 3x7 grid par unique paths print ─────────────────────────────────
//   m=3, n=7 — expected 28 paths stdout par dikhao
int main() {
    int m = 3, n = 7;
    cout << "Unique paths in " << m << "x" << n << " grid: " << uniquePaths(m, n) << endl;
    return 0;
}
