/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — LCS
 * FILE     : longest_common_subsequence.cpp
 * PROBLEM  : Longest common subsequence of two strings
 * LEETCODE : 1143 — Longest Common Subsequence
 * APPROACH : dp[i][j] = LCS of s1[0..i) and s2[0..j)
 * COMPLEX  : Time: O(n*m)  |  Space: O(n*m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LCS — do strings ka longest common subsequence ki length
// ────────────────────────────────────────────────────────────────────────────
// Subsequence = order same, contiguous zaroori nahi.
// dp[i][j] = a[0..i) aur b[0..j) ka LCS length.
// Chars match -> dono se ek peeche ka LCS + 1.
// No match -> max(LCS without a[i-1], LCS without b[j-1]).
// COMPLEX: Time O(n*m)  |  Space O(n*m)
// ════════════════════════════════════════════════════════════════════════════

// ── lcs: longest common subsequence length return karo ─────────────────────
//   1) dp (n+1)x(m+1) table — row/col 0 = empty string, LCS=0
//   2) Har (i,j) pe last chars compare karo
//   3) Match -> dp[i-1][j-1]+1 (dono me char include)
//   4) No match -> max(dp[i-1][j], dp[i][j-1]) — ek char skip
//   5) dp[n][m] = full strings ka LCS length
int lcs(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;           // common char mila — length +1
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // ek string ka char skip
    return dp[n][m];
}

// ── main: "abcde" aur "ace" pe LCS test ────────────────────────────────────
//   1) Do strings pass karo
//   2) LCS length print — expected 3 ("ace")
int main() {
    cout << lcs("abcde", "ace") << endl; // 3
    return 0;
}
