/*
 * ============================================================================
 * TOPIC    : Sliding Window — Longest Repeating Character Replacement
 * FILE     : longest_repeating_char_replace.cpp
 * PROBLEM  : Longest substring with at most k replacements
 * LEETCODE : 424 — Longest Repeating Character Replacement
 * APPROACH : Window valid if len - maxFreq <= k
 * COMPLEX  : Time: O(n)  |  Space: O(26)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LONGEST REPEATING WITH K REPLACEMENTS — Window validity trick
// ────────────────────────────────────────────────────────────────────────────
// Window valid jab: (window size - maxFreq) <= k
// Matlab baaki chars ko maxFreq wale me badalne pe k replacements kaafi
// maxFreq window me sabse zyada repeated char ki count
// Invalid pe l shrink — cnt[s[l]]--
// ════════════════════════════════════════════════════════════════════════════

// ── characterReplacement: max length with at most k changes ────────────────
//   1) cnt[26] — har char frequency in window
//   2) r expand: maxFreq update, cnt[s[r]]++
//   3) while (r-l+1 - maxFreq > k): left shrink
//   4) best = max window length
int characterReplacement(string s, int k) {
    vector<int> cnt(26, 0);
    int l = 0, maxFreq = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        maxFreq = max(maxFreq, ++cnt[s[r] - 'A']);
        while (r - l + 1 - maxFreq > k) // zyada replacements chahiye
            cnt[s[l++] - 'A']--;
        best = max(best, r - l + 1);
    }
    return best;
}

// ── main: "AABABBA", k=1 -> 4 ───────────────────────────────────────────────
int main() {
    cout << characterReplacement("AABABBA", 1) << endl; // 4
    return 0;
}
