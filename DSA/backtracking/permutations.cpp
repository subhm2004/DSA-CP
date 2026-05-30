/*
 * ============================================================================
 * TOPIC    : Backtracking — Permutations
 * FILE     : permutations.cpp
 * PROBLEM  : All permutations of distinct nums
 * LEETCODE : 46 — Permutations
 * APPROACH : Swap / used array backtracking
 * COMPLEX  : Time: O(n * n!)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> used;

    void bt(vector<int> &nums) {
        if (path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            bt(nums);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int> &nums) {
        used.assign(nums.size(), false);
        bt(nums);
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};
    cout << Solution().permute(nums).size() << endl; // 6
    return 0;
}
