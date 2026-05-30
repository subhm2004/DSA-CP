/*
 * ============================================================================
 * TOPIC    : LCS — Longest Common Subsequence
 * FILE     : lcs_bottom_up.cpp
 * PROBLEM  : Longest common subsequence of two strings
 * APPROACH : 2D DP — match / skip one character
 * COMPLEX  : Time: O(n * m)  |  Space: O(n * m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string lcsString(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1])
            i--;
        else
            j--;
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    string a = "abcde", b = "ace";
    string ans = lcsString(a, b);
    cout << "LCS(\"" << a << "\", \"" << b << "\") = \"" << ans
         << "\" (length " << ans.size() << ")\n";
    return 0;
}
