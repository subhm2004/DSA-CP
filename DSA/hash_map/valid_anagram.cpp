/*
 * ============================================================================
 * TOPIC    : Hash Map — Valid Anagram
 * FILE     : valid_anagram.cpp
 * PROBLEM  : Check if two strings are anagrams
 * LEETCODE : 242 — Valid Anagram
 * APPROACH : Frequency count array of size 26
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// VALID ANAGRAM — Character frequency match karo
// ────────────────────────────────────────────────────────────────────────────
// Anagram = same chars, different order
// cnt[26]: s se ++, t se -- — end me sab zero hona chahiye
// Length alag ho to turant false
// O(n) time, O(1) space (fixed 26)
// ════════════════════════════════════════════════════════════════════════════

// ── isAnagram: do strings anagram hain ya nahi ─────────────────────────────
//   1) size alag -> false
//   2) cnt[s[i]-'a']++, cnt[t[i]-'a']-- ek saath
//   3) cnt me koi non-zero -> false
//   4) sab zero -> true (same frequency)
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int cnt[26] = {};
    for (int i = 0; i < (int)s.size(); i++) {
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    for (int c : cnt) if (c) return false;
    return true;
}

// ── main: "anagram" vs "nagaram" -> YES ────────────────────────────────────
int main() {
    cout << (isAnagram("anagram", "nagaram") ? "YES" : "NO") << endl;
    return 0;
}
