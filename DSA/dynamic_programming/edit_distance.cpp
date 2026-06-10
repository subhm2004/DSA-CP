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

// ════════════════════════════════════════════════════════════════════════════
// EDIT DISTANCE — word1 ko word2 me convert karne ke min operations
// ────────────────────────────────────────────────────────────────────────────
// Teen operations: insert, delete, replace — har ek ki cost 1.
// dp[i][j] = a[0..i) ko b[0..j) me convert karne ka min cost.
// Base: empty string se convert = i inserts (dp[i][0]=i) ya j deletes (dp[0][j]=j).
// Match ho to free (dp[i-1][j-1]), warna teen options me se min + 1.
// COMPLEX: Time O(n*m)  |  Space O(n*m)
// ════════════════════════════════════════════════════════════════════════════

// ── editDistance: Levenshtein distance return karo ─────────────────────────
//   1) dp table (n+1) x (m+1) banao — extra row/col empty string ke liye
//   2) dp[i][0]=i (delete all), dp[0][j]=j (insert all) base fill
//   3) Har (i,j): chars match -> dp[i-1][j-1] (no op)
//   4) No match -> 1 + min(delete a[i-1], insert b[j-1], replace both)
//   5) dp[n][m] = final min edit distance
int editDistance(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;              // a ke chars sab delete
    for (int j = 0; j <= m; j++) dp[0][j] = j;              // b ke chars sab insert
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];               // match — koi operation nahi
            else
                dp[i][j] = 1 + min({dp[i - 1][j],          // delete from a
                                      dp[i][j - 1],          // insert into a
                                      dp[i - 1][j - 1]});    // replace char
    return dp[n][m];
}

// ── main: "horse" -> "ros" edit distance test ──────────────────────────────
//   1) Do strings pass karo
//   2) Min operations print — expected 3 (replace h->r, remove r, remove e)
int main() {
    cout << editDistance("horse", "ros") << endl; // 3
    return 0;
}
