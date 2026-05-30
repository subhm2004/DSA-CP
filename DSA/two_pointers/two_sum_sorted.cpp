/*
 * ============================================================================
 * TOPIC    : Two Pointers — Two Sum II (Sorted Array)
 * FILE     : two_sum_sorted.cpp
 * PROBLEM  : 1-indexed pair summing to target in sorted array
 * LEETCODE : 167 — Two Sum II
 * APPROACH : Two pointers from both ends
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> twoSumSorted(vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum == target) return {l + 1, r + 1};
        if (sum < target) l++;
        else r--;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    auto ans = twoSumSorted(nums, 9);
    cout << ans[0] << " " << ans[1] << endl; // 1 2
    return 0;
}
