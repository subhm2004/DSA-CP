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

// ════════════════════════════════════════════════════════════════════════════
// JUMP GAME I — Last index tak pahunch sakte ho?
// ────────────────────────────────────────────────────────────────────────────
// nums[i] = i se max kitne aage jump
// reach = ab tak sabse door reachable index
// Agar i > reach -> yahan tak nahi aa sakte -> false
// reach = max(reach, i + nums[i]) update karte jao
// ════════════════════════════════════════════════════════════════════════════

// ── canJump: last index reachable hai ya nahi ──────────────────────────────
//   1) reach=0 — ab tak kitna door ja sakte ho
//   2) har i: i > reach -> false (blocked)
//   3) reach = max(reach, i + nums[i])
//   4) end tak pahunche -> true
bool canJump(vector<int> &nums) {
    int reach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true;
}

// ── main: {2,3,1,1,4} -> YES ───────────────────────────────────────────────
int main() {
    vector<int> nums = {2,3,1,1,4};
    cout << (canJump(nums) ? "YES" : "NO") << endl;
    return 0;
}
