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

class Solution {
    vector<string> ans;
    string path;
    vector<string> pad = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void bt(const string &digits, int idx) {
        if (idx == (int)digits.size()) {
            ans.push_back(path);
            return;
        }
        for (char c : pad[digits[idx] - '0']) {
            path.push_back(c);
            bt(digits, idx + 1);
            path.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        bt(digits, 0);
        return ans;
    }
};

int main() {
    for (string &s : Solution().letterCombinations("23"))
        cout << s << " ";
    cout << endl; // ad ae af bd be bf cd ce cf
    return 0;
}
