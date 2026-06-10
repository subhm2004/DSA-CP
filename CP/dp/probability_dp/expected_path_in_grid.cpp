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

// ════════════════════════════════════════════════════════════════════════════
// EXPECTED PATH IN GRID — Probability DP (Top-Left to Bottom-Right)
// ────────────────────────────────────────────────────────────────────────────
// Grid me (0,0) se (m-1,n-1) tak pahunchne ki probability nikalo.
// Har step pe sirf RIGHT ya DOWN ja sakte ho — dono directions ki prob 0.5 hai.
// dp[j] = current row me column j pe pahunchne ki total probability (space optimized).
// Transition: dp[j] = 0.5 * dp[j] (top se) + 0.5 * dp[j-1] (left se).
// Pehli row/column me sirf ek direction available hoti hai.
// Time: O(m * n)  |  Space: O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── reachBottomRight: bottom-right cell tak pahunchne ki probability ──────
//   1) dp[0] = 1.0 — start cell (0,0) pe probability 1 hai
//   2) Har row i aur column j pe: (0,0) skip karo (already initialized)
//   3) fromTop = dp[j] * 0.5 agar i > 0 (upar se aane ki prob)
//   4) fromLeft = dp[j-1] * 0.5 agar j > 0 (left se aane ki prob)
//   5) dp[j] = fromTop + fromLeft — dono paths ki combined probability return
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

// ── main: sample grid pe reach probability print karo ─────────────────────
//   1) 3x3 grid set karo, reachBottomRight(m,n) call karo
//   2) bottom-right cell ki probability 6 decimal places me print karo
int main() {
    int m = 3, n = 3;
    cout << fixed << setprecision(6);
    cout << "Probability to reach (" << m - 1 << "," << n - 1 << ") in " << m << "x" << n
         << " grid = " << reachBottomRight(m, n) << endl;
    return 0;
}
