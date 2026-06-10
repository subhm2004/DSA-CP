/*
 * ============================================================================
 * TOPIC    : Edit Distance
 * FILE     : edit_distance_space_optimized.cpp
 * PROBLEM  : Edit distance with O(min(n,m)) space
 * APPROACH : Two rolling rows
 * COMPLEX  : Time: O(n * m)  |  Space: O(min(n, m))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EDIT DISTANCE — Space-Optimized (Two Rolling Rows)
// ────────────────────────────────────────────────────────────────────────────
// State: prev[j] = edit cost for previous row; curr[j] = current row.
// Same recurrence as 2D DP, bas poori table ki jagah 2 arrays.
// curr[0] = prev[0] + 1 har nayi row me (ek aur delete from a).
// Chhoti string columns me — space O(min(n,m)).
// Complexity: O(n*m) time, O(min(n,m)) space.
// ════════════════════════════════════════════════════════════════════════════

// ── minEditDistance: O(min(n,m)) space edit distance ────────────────────────
//   1) chhoti string ko b me rakho — kam columns
//   2) prev[j] = j base case (j inserts from empty)
//   3) har char ca of a ke liye curr row bharo, phir prev = curr
//   4) prev[m] = final edit distance
int minEditDistance(const string &a, const string &b) {
    if (a.size() < b.size())
        return minEditDistance(b, a);

    int m = b.size();
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++)
        prev[j] = j; // row 0: empty a se b[0..j-1] banane me j inserts

    for (char ca : a) {
        curr[0] = prev[0] + 1; // naya char a me — ek extra delete cost
        for (int j = 1; j <= m; j++) {
            if (ca == b[j - 1])
                curr[j] = prev[j - 1]; // match — diagonal se copy
            else
                curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
                // delete (prev[j]), insert (curr[j-1]), replace (prev[j-1])
        }
        prev = curr; // rolling row — current ab previous ban jayegi
    }

    return prev[m];
}

// ── main: space-optimized edit distance demo ────────────────────────────────
//   1) "intention" -> "execution" distance print karo
int main() {
    string a = "intention", b = "execution";
    cout << "Edit distance = " << minEditDistance(a, b) << endl;
    return 0;
}
