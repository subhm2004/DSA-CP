/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : three_sum.cpp
 * PROBLEM  : Find all unique triplets with sum zero
 * APPROACH : Sort + fix i + two pointers on rest
 * COMPLEX  : Time: O(n^2)  |  Space: O(1) extra
 * LEETCODE : 15 — 3Sum
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 3SUM — Sort + Fix First Element + Two Pointers
// ────────────────────────────────────────────────────────────────────────────
// nums[i] + nums[l] + nums[r] = 0 dhundhna hai
//   1) sort karo — duplicate skip aur two pointer possible
//   2) har i fix karo (pehla element of triplet)
//   3) baaki [l, r] pe classic two sum on target = -nums[i]
//   4) triplet milne pe duplicates skip (l/r aage badhao jab tak same value)
// COMPLEX: O(n²) — outer i + inner two pointer
// ════════════════════════════════════════════════════════════════════════════

// ── threeSum: saare unique triplets jinka sum = 0 ──
//   1) sort(nums)
//   2) i = 0..n-1: agar nums[i] == nums[i-1] skip (duplicate triplet avoid)
//   3) l = i+1, r = n-1
//   4) sum == 0 → triplet save, duplicate l/r skip, dono pointers move
//   5) sum < 0 → l++ (bada element chahiye)
//   6) sum > 0 → r-- (chhota element chahiye)
vector<vector<int>> threeSum(vector<int> nums)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue; // same first element → duplicate triplets

        int l = i + 1, r = n - 1;
        while (l < r)
        {
            long long sum = (long long)nums[i] + nums[l] + nums[r];
            if (sum == 0)
            {
                ans.push_back({nums[i], nums[l], nums[r]});
                // duplicate second/third element skip
                while (l < r && nums[l] == nums[l + 1])
                    l++;
                while (l < r && nums[r] == nums[r - 1])
                    r--;
                l++;
                r--;
            }
            else if (sum < 0)
                l++;
            else
                r--;
        }
    }
    return ans;
}

int main()
{
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    for (auto &t : threeSum(nums))
        cout << t[0] << " " << t[1] << " " << t[2] << endl;
    // Output: -1 -1 2, -1 0 1
    return 0;
}
