/*
 * ============================================================================
 * TOPIC    : Partition DP
 * FILE     : palindrome_partitioning.cpp
 * PROBLEM  : Minimum cuts to partition string into palindrome substrings
 * APPROACH : Partition DP — try all last palindrome pieces
 * COMPLEX  : Time: O(n^2)  |  Space: O(n^2)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string &s, int i, int j) {
    while (i < j) {
        if (s[i++] != s[j--])
            return false;
    }
    return true;
}

int minCuts(string s) {
    int n = s.size();
    vector<vector<bool>> pal(n, vector<bool>(n, false));
    vector<int> dp(n, INT_MAX);

    for (int i = 0; i < n; i++)
        pal[i][i] = true;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && (len == 2 || pal[i + 1][j - 1]))
                pal[i][j] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        if (pal[0][i])
            dp[i] = 0;
        else {
            for (int j = 1; j <= i; j++) {
                if (pal[j][i])
                    dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }
    }

    return dp[n - 1];
}

int main() {
    string s = "aabcc";
    cout << "Minimum palindrome cuts for \"" << s << "\": " << minCuts(s) << endl;
    return 0;
}
