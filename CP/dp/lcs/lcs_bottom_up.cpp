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

// ════════════════════════════════════════════════════════════════════════════
// LCS — Bottom-Up 2D DP + Reconstruction
// ────────────────────────────────────────────────────────────────────────────
// State: dp[i][j] = LCS length of a[0..i-1] aur b[0..j-1].
// Match: dp[i][j] = dp[i-1][j-1] + 1 (dono chars same, dono include karo).
// Mismatch: max(dp[i-1][j], dp[i][j-1]) — ek char skip karo.
// Backtrack: dp table se actual LCS string reconstruct karo.
// Complexity: O(n*m) time, O(n*m) space.
// ════════════════════════════════════════════════════════════════════════════

// ── lcsString: LCS length + actual subsequence string ───────────────────────
//   1) dp table bharo — match pe +1, mismatch pe max of up/left
//   2) dp[n][m] se backtrack: match -> char add, else jahan value zyada ho wahan jao
//   3) reverse karo kyunki backtrack end se start tak chalta hai
//   4) reconstructed LCS string return
string lcsString(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1; // match — dono chars LCS me aate hain
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // skip a[i-1] ya b[j-1]
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
            i--; // upar wala path zyada promising — a[i-1] skip
        else
            j--; // left wala path zyada promising — b[j-1] skip
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// ── main: sample LCS demo ───────────────────────────────────────────────────
//   1) do strings set karo, lcsString call karo
//   2) LCS string aur length print karo
int main() {
    string a = "abcde", b = "ace";
    string ans = lcsString(a, b);
    cout << "LCS(\"" << a << "\", \"" << b << "\") = \"" << ans
         << "\" (length " << ans.size() << ")\n";
    return 0;
}
