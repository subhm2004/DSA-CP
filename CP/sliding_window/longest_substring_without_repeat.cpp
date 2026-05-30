/*
 * ============================================================================
 * TOPIC    : Sliding Window
 * FILE     : longest_substring_without_repeat.cpp
 * PROBLEM  : Longest substring without repeating characters
 * APPROACH : Expand r, shrink l when duplicate seen (hash map)
 * COMPLEX  : Time: O(n)  |  Space: O(alphabet)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(const string &s) {
    vector<int> last(256, -1);
    int best = 0, l = 0;

    for (int r = 0; r < (int)s.size(); r++) {
        if (last[s[r]] >= l)
            l = last[s[r]] + 1;
        last[s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    string s = "abcabcbb";
    cout << "Longest unique substring length = " << lengthOfLongestSubstring(s) << endl;
    return 0;
}
