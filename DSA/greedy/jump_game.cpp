/*
 * ============================================================================
 * TOPIC    : Greedy — Jump Game
 * FILE     : jump_game.cpp
 * PROBLEM  : Can reach last index?
 * LEETCODE : 55 — Jump Game
 * APPROACH : Track farthest reachable index
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool canJump(vector<int> &nums) {
    int reach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true;
}

int main() {
    vector<int> nums = {2,3,1,1,4};
    cout << (canJump(nums) ? "YES" : "NO") << endl;
    return 0;
}
