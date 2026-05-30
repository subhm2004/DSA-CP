/*
 * ============================================================================
 * TOPIC    : Backtracking — Combination Sum
 * FILE     : combination_sum.cpp
 * PROBLEM  : Combinations summing to target (reuse allowed)
 * LEETCODE : 39 — Combination Sum
 * APPROACH : Backtrack; pick same index for reuse
 * COMPLEX  : Time: O(2^target)  |  Space: O(target)
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
            if (c[i] > target) break;
            path.push_back(c[i]);
            bt(c, target - c[i], i, path);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        bt(candidates, target, 0, path);
        return ans;
    }
};

int main() {
    vector<int> c = {2, 3, 6, 7};
    cout << Solution().combinationSum(c, 7).size() << endl; // 2
    return 0;
}
