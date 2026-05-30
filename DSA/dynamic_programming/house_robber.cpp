/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — House Robber
 * FILE     : house_robber.cpp
 * PROBLEM  : Max money robbing non-adjacent houses
 * LEETCODE : 198 — House Robber
 * APPROACH : dp[i] = max(rob i + dp[i-2], dp[i-1])
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int rob(const vector<int> &nums) {
    int take = 0, skip = 0;
    for (int x : nums) {
        int next = max(skip + x, take);
        skip = take;
        take = next;
    }
    return take;
}

int main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << rob(nums) << endl; // 12
    return 0;
}
