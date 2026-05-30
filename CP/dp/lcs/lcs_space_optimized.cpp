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

int lcsLength(const string &a, const string &b) {
    if (a.size() < b.size())
        return lcsLength(b, a);

    int m = b.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (char ca : a) {
        for (int j = 1; j <= m; j++) {
            if (ca == b[j - 1])
                curr[j] = prev[j - 1] + 1;
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }

    return prev[m];
}

int main() {
    string a = "AGGTAB", b = "GXTXAYB";
    cout << "LCS length = " << lcsLength(a, b) << endl;
    return 0;
}
