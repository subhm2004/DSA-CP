/*
 * ============================================================================
 * TOPIC    : Arrays — Kadane's Algorithm
 * FILE     : kadanes_max_subarray.cpp
 * PROBLEM  : Maximum sum contiguous subarray
 * LEETCODE : 53 — Maximum Subarray
 * APPROACH : cur = max(x, cur+x); best = max(best, cur)
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxSubArray(vector<int> &nums) {
    int cur = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        cur = max(nums[i], cur + nums[i]);
        best = max(best, cur);
    }
    return best;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl; // 6
    return 0;
}
