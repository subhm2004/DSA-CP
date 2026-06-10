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

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME PARTITIONING — Minimum Cuts (Partition DP)
// ────────────────────────────────────────────────────────────────────────────
// Pehle pal[i][j] precompute — s[i..j] palindrome hai ya nahi.
// dp[i] = s[0..i] ko palindrome pieces me todne ke minimum cuts.
// Agar pal[0][i] true hai to dp[i]=0 (poora prefix ek palindrome).
// Warna har j try karo jahan pal[j][i] true — dp[i] = min(dp[j-1]+1).
// ════════════════════════════════════════════════════════════════════════════

// ── isPalindrome: s[i..j] palindrome check (two pointers) ─────────────────
//   1) i left se, j right se andar aate hain
//   2) s[i] != s[j] ho to false — mismatch mil gaya
//   3) i >= j tak sab match — true return
bool isPalindrome(const string &s, int i, int j) {
    while (i < j) {
        if (s[i++] != s[j--])
            return false;
    }
    return true;
}

// ── minCuts: minimum cuts for palindrome partition ──────────────────────────
//   1) pal[i][j] table banao — length 1 palindrome; len>=2 pe expand karo
//   2) dp[i] = s[0..i] ke minimum cuts; pal[0][i] true ho to dp[i]=0
//   3) har j (1..i) try karo — agar pal[j][i] true, last piece valid hai
//   4) transition: dp[i] = min(dp[i], dp[j-1] + 1) — ek cut j ke pehle
//   5) dp[n-1] return — poori string ke minimum cuts
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

// ── main: sample string par minimum cuts print ──────────────────────────────
//   "aabcc" ke liye minCuts call karke result stdout par dikhao
int main() {
    string s = "aabcc";
    cout << "Minimum palindrome cuts for \"" << s << "\": " << minCuts(s) << endl;
    return 0;
}
