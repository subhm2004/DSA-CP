/*
 * ============================================================================
 * TOPIC    : Backtracking — Subsets (Power Set)
 * FILE     : subsets.cpp
 * PROBLEM  : All subsets of distinct integers
 * LEETCODE : 78 — Subsets
 * APPROACH : Include / exclude each element (pick from index)
 * COMPLEX  : Time: O(n * 2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    void bt(vector<int> &nums, int idx) {
        ans.push_back(path);
        for (int i = idx; i < (int)nums.size(); i++) {
            path.push_back(nums[i]);
            bt(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int> &nums) {
        bt(nums, 0);
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};
    cout << Solution().subsets(nums).size() << endl; // 8
    return 0;
}
