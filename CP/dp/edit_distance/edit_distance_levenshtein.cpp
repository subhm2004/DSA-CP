/*
 * ============================================================================
 * TOPIC    : Edit Distance
 * FILE     : edit_distance_levenshtein.cpp
 * PROBLEM  : Minimum operations to convert word1 → word2
 *            (insert, delete, replace — each cost 1)
 * APPROACH : 2D DP — same framework as LCS with cost on mismatch
 * COMPLEX  : Time: O(n * m)  |  Space: O(n * m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EDIT DISTANCE (LEVENSHTEIN) — 2D DP
// ────────────────────────────────────────────────────────────────────────────
// State: dp[i][j] = min edits to convert a[0..i-1] -> b[0..j-1].
// Base: dp[i][0]=i (i deletes), dp[0][j]=j (j inserts).
// Match: dp[i][j] = dp[i-1][j-1] (free, koi edit nahi).
// Mismatch: 1 + min(delete a[i-1], insert b[j-1], replace both).
// Complexity: O(n*m) time, O(n*m) space.
// ════════════════════════════════════════════════════════════════════════════

// ── minEditDistance: Levenshtein distance between two strings ───────────────
//   1) first row/column base cases bharo (sirf insert/delete se convert)
//   2) har cell me match ho to diagonal copy, warna 3 operations me se min
//   3) dp[i-1][j] = delete, dp[i][j-1] = insert, dp[i-1][j-1] = replace
//   4) dp[n][m] return — poora conversion cost
int minEditDistance(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = i; // a[0..i-1] ko empty string banane ke liye i deletes
    for (int j = 0; j <= m; j++)
        dp[0][j] = j; // empty se b[0..j-1] banane ke liye j inserts

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1]; // chars same — koi edit nahi
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                // delete a[i-1], insert b[j-1], ya replace — teeno me se cheapest
        }
    }

    return dp[n][m];
}

// ── main: Levenshtein distance demo ─────────────────────────────────────────
//   1) "horse" -> "ros" conversion cost print karo
int main() {
    string a = "horse", b = "ros";
    cout << "Edit distance(\"" << a << "\", \"" << b << "\") = "
         << minEditDistance(a, b) << endl;
    return 0;
}
