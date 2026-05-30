/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — House Robber II (circular)
 * FILE     : house_robber_2.cpp
 * PROBLEM  : Houses in circle — first and last adjacent
 * LEETCODE : 213 — House Robber II
 * APPROACH : max(rob range [0..n-2], rob range [1..n-1])
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int robLinear(const vector<int> &nums, int lo, int hi) {
    int take = 0, skip = 0;
    for (int i = lo; i <= hi; i++) {
        int next = max(skip + nums[i], take);
        skip = take;
        take = next;
    }
    return take;
}

int robCircular(const vector<int> &nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
}

int main() {
    vector<int> nums = {2, 3, 2};
    cout << robCircular(nums) << endl; // 3
    return 0;
}
