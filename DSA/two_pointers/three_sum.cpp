/*
 * ============================================================================
 * TOPIC    : Two Pointers — 3Sum
 * FILE     : three_sum.cpp
 * PROBLEM  : All unique triplets summing to zero
 * LEETCODE : 15 — 3Sum
 * APPROACH : Sort + fix i, two pointers on rest
 * COMPLEX  : Time: O(n^2)  |  Space: O(1) extra
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 3SUM — Sort + fix first element, two pointers on baaki
// ────────────────────────────────────────────────────────────────────────────
// nums sort -> duplicate skip aasaan
// Har i fix: l=i+1, r=n-1 — target = -nums[i]
// sum==0 -> triplet save, duplicates skip, l++, r--
// sum<0 -> l++ (bada chahiye), sum>0 -> r--
// ════════════════════════════════════════════════════════════════════════════

// ── threeSum: saari unique triplets jinka sum 0 ────────────────────────────
//   1) nums sort karo
//   2) har i: duplicate i skip (nums[i]==nums[i-1])
//   3) l,r two pointers: sum compare with 0
//   4) sum==0 -> ans push, duplicate l/r skip, move pointers
//   5) sum<0 -> l++, sum>0 -> r--
vector<vector<int>> threeSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        if (i && nums[i] == nums[i - 1]) continue; // same first element skip
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                ans.push_back({nums[i], nums[l], nums[r]});
                while (l < r && nums[l] == nums[l + 1]) l++; // duplicate skip
                while (l < r && nums[r] == nums[r - 1]) r--;
                l++; r--;
            } else if (sum < 0) l++;
            else r--;
        }
    }
    return ans;
}

// ── main: nums -> triplets print ───────────────────────────────────────────
int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    for (auto &t : threeSum(nums)) {
        cout << t[0] << " " << t[1] << " " << t[2] << endl;
    }
    return 0;
}
