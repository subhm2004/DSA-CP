/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Edit Distance (Levenshtein)
 * FILE     : edit_distance.cpp
 * PROBLEM  : Min insert/delete/replace to convert word1 → word2
 * LEETCODE : 72 — Edit Distance
 * APPROACH : dp[i][j] from dp[i-1][j], dp[i][j-1], dp[i-1][j-1]
 * COMPLEX  : Time: O(n*m)  |  Space: O(n*m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int editDistance(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
    return dp[n][m];
}

int main() {
    cout << editDistance("horse", "ros") << endl; // 3
    return 0;
}
