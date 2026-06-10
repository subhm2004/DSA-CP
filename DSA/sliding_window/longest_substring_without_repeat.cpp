/*
 * ============================================================================
 * TOPIC    : Sliding Window — Longest Substring Without Repeating
 * FILE     : longest_substring_without_repeat.cpp
 * PROBLEM  : Max length substring with all unique chars
 * LEETCODE : 3 — Longest Substring Without Repeating Characters
 * APPROACH : Expand window; shrink when duplicate via last index map
 * COMPLEX  : Time: O(n)  |  Space: O(alphabet)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LONGEST UNIQUE SUBSTRING — Sliding window + last seen map
// ────────────────────────────────────────────────────────────────────────────
// Window [l..r] me duplicate nahi hona chahiye
// last[c] = char c ka last index — duplicate pe l = last[c]+1
// best = max window length r-l+1
// O(n) — har char ek baar process
// ════════════════════════════════════════════════════════════════════════════

// ── lengthOfLongestSubstring: max unique substring length ──────────────────
//   1) last[256]=-1 — har char ka last index
//   2) r expand: agar last[s[r]] >= l -> l jump (duplicate hatao)
//   3) last[s[r]] = r update
//   4) best = max(best, r-l+1)
int lengthOfLongestSubstring(string s) {
    vector<int> last(256, -1);
    int best = 0, l = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        if (last[s[r]] >= l) l = last[s[r]] + 1; // duplicate — window shrink
        last[s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// ── main: "abcabcbb" -> 3 ("abc") ──────────────────────────────────────────
int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl; // 3
    return 0;
}
