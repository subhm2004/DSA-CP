/*
 * ============================================================================
 * TOPIC    : Greedy — Jump Game II (minimum jumps)
 * FILE     : jump_game_2.cpp
 * PROBLEM  : Minimum jumps to last index
 * LEETCODE : 45 — Jump Game II
 * APPROACH : BFS-like greedy layers — end of current jump range
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int jump(vector<int> &nums) {
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == curEnd) {
            jumps++;
            curEnd = farthest;
        }
    }
    return jumps;
}

int main() {
    vector<int> nums = {2,3,1,1,4};
    cout << jump(nums) << endl; // 2
    return 0;
}
