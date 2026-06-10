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

// ════════════════════════════════════════════════════════════════════════════
// TWO SUM — Hash map se O(n) pair dhundho
// ────────────────────────────────────────────────────────────────────────────
// Har element ke liye need = target - nums[i]
// Agar need pehle map me hai -> pair mil gaya
// Warna nums[i] -> index map me store karo
// Ek hi pass me answer — brute force O(n²) se better
// ════════════════════════════════════════════════════════════════════════════

// ── twoSum: do indices jinka sum target ho ─────────────────────────────────
//   1) mp: value -> index (pehli occurrence)
//   2) har i pe need = target - nums[i]
//   3) mp.count(need) -> return {mp[need], i}
//   4) warna mp[nums[i]] = i store karo
vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < (int)nums.size(); i++) {
        int need = target - nums[i]; // dusra number kya hona chahiye
        if (mp.count(need)) return {mp[need], i};
        mp[nums[i]] = i;
    }
    return {};
}

// ── main: {2,7,11,15}, target=9 -> indices 0,1 ─────────────────────────────
int main() {
    vector<int> nums = {2, 7, 11, 15};
    auto ans = twoSum(nums, 9);
    cout << ans[0] << " " << ans[1] << endl; // 0 1
    return 0;
}
