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

// ════════════════════════════════════════════════════════════════════════════
// JUMP GAME II — Minimum jumps last tak
// ────────────────────────────────────────────────────────────────────────────
// BFS layers jaisa: ek jump me jitna door ja sakte, woh ek "level"
// curEnd = current jump se max reachable index
// farthest = is level me sabse door kahan ja sakte
// i == curEnd -> jump count++, curEnd = farthest (nayi layer)
// ════════════════════════════════════════════════════════════════════════════

// ── jump: minimum jumps to reach last index ────────────────────────────────
//   1) jumps=0, curEnd=0, farthest=0
//   2) last se ek pehle tak: farthest = max(farthest, i+nums[i])
//   3) i == curEnd -> jumps++, curEnd = farthest (nayi jump layer)
//   4) jumps return
int jump(vector<int> &nums) {
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == curEnd) {
            jumps++;
            curEnd = farthest; // is jump ke baad naya boundary
        }
    }
    return jumps;
}

// ── main: {2,3,1,1,4} -> 2 jumps ───────────────────────────────────────────
int main() {
    vector<int> nums = {2,3,1,1,4};
    cout << jump(nums) << endl; // 2
    return 0;
}
