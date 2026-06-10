/*
 * ============================================================================
 * TOPIC    : LCS — Longest Common Subsequence
 * FILE     : lcs_space_optimized.cpp
 * PROBLEM  : LCS length only (space optimized)
 * APPROACH : Rolling 1D DP array
 * COMPLEX  : Time: O(n * m)  |  Space: O(min(n, m))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LCS — Space-Optimized Rolling 1D DP
// ────────────────────────────────────────────────────────────────────────────
// State: curr[j] = LCS length for current row i aur b[0..j-1].
// prev[] = previous row; curr[] = current row — sirf 2 rows chahiye.
// Match: curr[j] = prev[j-1] + 1; Mismatch: max(prev[j], curr[j-1]).
// Chhoti string ko columns me rakho taaki space O(min(n,m)) ho.
// Complexity: O(n*m) time, O(min(n,m)) space.
// ════════════════════════════════════════════════════════════════════════════

// ── lcsLength: sirf LCS ki length (string nahi) ─────────────────────────────
//   1) chhoti string ko b me swap karo — kam columns = kam space
//   2) har char ca of a ke liye ek row compute karo (prev -> curr)
//   3) match/mismatch same recurrence, bas 2 arrays use karo
//   4) prev[m] = final LCS length
int lcsLength(const string &a, const string &b) {
    if (a.size() < b.size())
        return lcsLength(b, a);

    int m = b.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (char ca : a) {
        for (int j = 1; j <= m; j++) {
            if (ca == b[j - 1])
                curr[j] = prev[j - 1] + 1; // diagonal + 1 — chars match
            else
                curr[j] = max(prev[j], curr[j - 1]); // up ya left se best
        }
        prev = curr; // current row ab next iteration ke liye previous ban jayegi
    }

    return prev[m];
}

// ── main: space-optimized LCS length demo ───────────────────────────────────
//   1) do strings set karo, sirf length print karo
int main() {
    string a = "AGGTAB", b = "GXTXAYB";
    cout << "LCS length = " << lcsLength(a, b) << endl;
    return 0;
}
