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

int lcs(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}

int main() {
    cout << lcs("abcde", "ace") << endl; // 3
    return 0;
}
