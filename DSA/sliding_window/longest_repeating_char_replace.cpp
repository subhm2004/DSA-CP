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

int characterReplacement(string s, int k) {
    vector<int> cnt(26, 0);
    int l = 0, maxFreq = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        maxFreq = max(maxFreq, ++cnt[s[r] - 'A']);
        while (r - l + 1 - maxFreq > k)
            cnt[s[l++] - 'A']--;
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    cout << characterReplacement("AABABBA", 1) << endl; // 4
    return 0;
}
