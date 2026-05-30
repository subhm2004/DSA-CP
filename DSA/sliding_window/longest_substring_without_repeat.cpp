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

int lengthOfLongestSubstring(string s) {
    vector<int> last(256, -1);
    int best = 0, l = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        if (last[s[r]] >= l) l = last[s[r]] + 1;
        last[s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl; // 3
    return 0;
}
