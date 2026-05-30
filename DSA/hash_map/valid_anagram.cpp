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

int main() {
    cout << (isAnagram("anagram", "nagaram") ? "YES" : "NO") << endl;
    return 0;
}
