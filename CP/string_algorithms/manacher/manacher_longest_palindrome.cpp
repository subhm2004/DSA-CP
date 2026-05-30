/*
 * ============================================================================
 * TOPIC    : Manacher's Algorithm
 * FILE     : manacher_longest_palindrome.cpp
 * PROBLEM  : Longest palindromic substring in O(n)
 * APPROACH : Expand around centers with palindrome radius array
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(string s) {
    string t = "#";
    for (char c : s)
        t += c, t += '#';

    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0, bestLen = 0, bestCenter = 0;

    for (int i = 0; i < n; i++) {
        if (i < right)
            p[i] = min(right - i, p[2 * center - i]);

        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > bestLen) {
            bestLen = p[i];
            bestCenter = i;
        }
    }

    int start = (bestCenter - bestLen) / 2;
    return s.substr(start, bestLen);
}

int main() {
    string s = "babad";
    cout << "Longest palindrome in \"" << s << "\": \"" << longestPalindrome(s) << "\"\n";
    return 0;
}
