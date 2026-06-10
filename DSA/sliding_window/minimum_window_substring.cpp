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

// ════════════════════════════════════════════════════════════════════════════
// MINIMUM WINDOW SUBSTRING — Expand jab tak valid, shrink minimum ke liye
// ────────────────────────────────────────────────────────────────────────────
// need[c] = t me c kitni baar chahiye
// have[c] = current window me kitni baar hai
// formed = kitne unique chars ki need poori ho gayi
// formed == required -> valid window — shrink l se, best update
// ════════════════════════════════════════════════════════════════════════════

// ── minWindow: s me t ka sabse chhota substring ────────────────────────────
//   1) need array banao t se, required = distinct chars count
//   2) r expand: need wale chars have me count, formed update
//   3) jab formed==required: bestLen update, l se shrink
//   4) shrink pe have kam -> formed--, l++
//   5) best substring return (ya "" agar nahi mila)
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
            if (have[s[r]] == need[s[r]]) formed++; // is char ki need poori
        }
        while (formed == required) {
            if (r - l + 1 < bestLen) {
                bestLen = r - l + 1;
                bestL = l;
            }
            if (need[s[l]] > 0) {
                have[s[l]]--;
                if (have[s[l]] < need[s[l]]) formed--; // ab invalid
            }
            l++;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

// ── main: s="ADOBECODEBANC", t="ABC" -> "BANC" ──────────────────────────────
int main() {
    cout << minWindow("ADOBECODEBANC", "ABC") << endl; // BANC
    return 0;
}
