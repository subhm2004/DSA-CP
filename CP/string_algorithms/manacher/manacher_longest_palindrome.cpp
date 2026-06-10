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

// longestPalindrome — Manacher: O(n) me sabse lamba palindromic substring.
// Step 1: s ko "#c#c#..." transform karo — odd/even dono centers ek saath handle.
// Step 2: p[i] = radius at i; agar i < right to mirror se seed: min(right-i, p[2*center-i]).
// Step 3: While se expand jab tak t[i±p[i]±1] match — palindrome boundary badhao.
// Step 4: Naya right boundary mile to center/right update; best radius track karke original s se extract.
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

// main — sample string pe Manacher chalao; longest palindrome print karo.
int main() {
    string s = "babad";
    cout << "Longest palindrome in \"" << s << "\": \"" << longestPalindrome(s) << "\"\n";
    return 0;
}
