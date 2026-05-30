/*
 * ============================================================================
 * TOPIC    : Backtracking — Combination Sum II
 * FILE     : combination_sum_ii.cpp
 * PROBLEM  : Unique combinations (each number once, no duplicate sets)
 * LEETCODE : 40 — Combination Sum II
 * APPROACH : Sort + skip duplicate at same recursion level
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> ans;

    void bt(vector<int> &c, int target, int start, vector<int> &path) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }
        for (int i = start; i < (int)c.size(); i++) {
            if (i > start && c[i] == c[i - 1]) continue;
            if (c[i] > target) break;
            path.push_back(c[i]);
            bt(c, target - c[i], i + 1, path);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        bt(candidates, target, 0, path);
        return ans;
    }
};

int main() {
    vector<int> c = {10, 1, 2, 7, 6, 1, 5};
    cout << Solution().combinationSum2(c, 8).size() << endl; // 4
    return 0;
}
