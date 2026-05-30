/*
 * ============================================================================
 * TOPIC    : Backtracking — Palindrome Partitioning
 * FILE     : palindrome_partitioning.cpp
 * PROBLEM  : Partition string so every part is palindrome
 * LEETCODE : 131 — Palindrome Partitioning
 * APPROACH : Try all cuts; check palindrome for substring
 * COMPLEX  : Time: O(n * 2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<string>> ans;
    vector<string> path;

    bool isPal(const string &s) {
        int l = 0, r = s.size() - 1;
        while (l < r)
            if (s[l++] != s[r--]) return false;
        return true;
    }

    void bt(const string &s, int start) {
        if (start == (int)s.size()) {
            ans.push_back(path);
            return;
        }
        for (int end = start; end < (int)s.size(); end++) {
            string sub = s.substr(start, end - start + 1);
            if (!isPal(sub)) continue;
            path.push_back(sub);
            bt(s, end + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        bt(s, 0);
        return ans;
    }
};

int main() {
    cout << Solution().partition("aab").size() << endl; // 2
    return 0;
}
