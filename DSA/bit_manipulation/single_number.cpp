/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Single Number
 * FILE     : single_number.cpp
 * PROBLEM  : Every element appears twice except one
 * LEETCODE : 136 — Single Number
 * APPROACH : XOR all elements — pairs cancel to 0
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SINGLE NUMBER — sab do baar aate hain, ek sirf ek baar
// ────────────────────────────────────────────────────────────────────────────
// XOR property: a ^ a = 0, a ^ 0 = a
// Same number do baar XOR -> cancel ho jata hai
// Sirf unique number bachega — wahi answer
// Extra space nahi — O(1) space, O(n) time
// ════════════════════════════════════════════════════════════════════════════

// ── singleNumber: woh element jo ek hi baar hai ───────────────────────────
//   1) ans = 0 initialize
//   2) har x pe ans ^= x — pairs cancel, unique bachta hai
//   3) loop ke baad ans = single number
//   4) ans return
int singleNumber(vector<int> &nums) {
    int ans = 0;
    for (int x : nums) ans ^= x;
    return ans;
}

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << singleNumber(nums) << endl; // 4
    return 0;
}
