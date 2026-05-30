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

int minEditDistance(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }

    return dp[n][m];
}

int main() {
    string a = "horse", b = "ros";
    cout << "Edit distance(\"" << a << "\", \"" << b << "\") = "
         << minEditDistance(a, b) << endl;
    return 0;
}
