/*
 * ============================================================================
 * TOPIC    : Sliding Window — Minimum Window Substring
 * FILE     : minimum_window_substring.cpp
 * PROBLEM  : Smallest window in s containing all chars of t
 * LEETCODE : 76 — Minimum Window Substring
 * APPROACH : Expand/shrink window tracking required char counts
 * COMPLEX  : Time: O(n)  |  Space: O(alphabet)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string minWindow(string s, string t) {
    if (t.empty()) return "";
    vector<int> need(128, 0), have(128, 0);
    int required = 0;
    for (char c : t) {
        if (need[c]++ == 0) required++;
    }

    int formed = 0, l = 0, bestLen = INT_MAX, bestL = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        if (need[s[r]] > 0) {
            have[s[r]]++;
            if (have[s[r]] == need[s[r]]) formed++;
        }
        while (formed == required) {
            if (r - l + 1 < bestLen) {
                bestLen = r - l + 1;
                bestL = l;
            }
            if (need[s[l]] > 0) {
                have[s[l]]--;
                if (have[s[l]] < need[s[l]]) formed--;
            }
            l++;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

int main() {
    cout << minWindow("ADOBECODEBANC", "ABC") << endl; // BANC
    return 0;
}
