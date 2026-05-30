/*
 * ============================================================================
 * TOPIC    : Hash Map — Two Sum
 * FILE     : two_sum_hashmap.cpp
 * PROBLEM  : Indices where nums[i]+nums[j]=target
 * LEETCODE : 1 — Two Sum
 * APPROACH : Store value→index; check target-nums[i]
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < (int)nums.size(); i++) {
        int need = target - nums[i];
        if (mp.count(need)) return {mp[need], i};
        mp[nums[i]] = i;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    auto ans = twoSum(nums, 9);
    cout << ans[0] << " " << ans[1] << endl; // 0 1
    return 0;
}
