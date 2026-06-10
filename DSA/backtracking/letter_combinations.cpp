/*
 * ============================================================================
 * TOPIC    : Backtracking — Letter Combinations of Phone Number
 * FILE     : letter_combinations.cpp
 * PROBLEM  : All strings from phone digit mapping
 * LEETCODE : 17 — Letter Combinations of a Phone Number
 * APPROACH : Backtrack each digit position
 * COMPLEX  : Time: O(4^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LETTER COMBINATIONS — phone digits se saari possible letter strings banao
// ────────────────────────────────────────────────────────────────────────────
// Funda: har digit ke mapped letters par ek-ek try karo (backtrack)
// Jaise "23" -> ad, ae, af, bd, be, bf, cd, ce, cf
// COMPLEX: Time O(4^n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<string> ans;
    string path;
    vector<string> pad = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    // ── bt: idx-th digit ke letters se combination build karo ──────────────
    //   1) saare digits process ho gaye -> path ko ans me save
    //   2) current digit ka letter set pad[digit] se lo
    //   3) har letter pick karo, idx+1 par recurse
    //   4) backtrack: pop_back karke agla letter try
    void bt(const string &digits, int idx) {
        if (idx == (int)digits.size()) {
            ans.push_back(path); // complete combination ready
            return;
        }
        for (char c : pad[digits[idx] - '0']) { // digit -> mapped letters
            path.push_back(c);
            bt(digits, idx + 1); // agla digit process karo
            path.pop_back(); // current letter hatao — agla option try
        }
    }

public:
    // ── letterCombinations: empty input handle + bt start ─────────────────
    //   1) digits empty ho to {} return
    //   2) idx 0 se backtrack
    //   3) saari combinations return
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        bt(digits, 0);
        return ans;
    }
};

// ── main: "23" ke saare combinations print ─────────────────────────────────
//   1) letterCombinations call
//   2) har string space-separated print
int main() {
    for (string &s : Solution().letterCombinations("23"))
        cout << s << " ";
    cout << endl; // ad ae af bd be bf cd ce cf
    return 0;
}
