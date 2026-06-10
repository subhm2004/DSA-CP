/*
 * ============================================================================
 * TOPIC    : LIS — Longest Increasing Subsequence
 * FILE     : lis_dp_o_n2.cpp
 * PROBLEM  : Find length and one LIS of the array
 * APPROACH : dp[i] = LIS ending at index i — O(n^2)
 * COMPLEX  : Time: O(n^2)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LIS — O(n^2) DP with Path Reconstruction
// ────────────────────────────────────────────────────────────────────────────
// State: dp[i] = LIS length ending exactly at index i (minimum 1).
// Transition: har j < i jahan nums[j] < nums[i], dp[i] = max(dp[i], dp[j]+1).
// prev[i] = kis index se extend hua — backtrack ke liye parent pointer.
// Complexity: O(n^2) time, O(n) space.
// ════════════════════════════════════════════════════════════════════════════

// ── lisWithPath: LIS length + ek valid LIS sequence ─────────────────────────
//   1) dp[i]=1, prev[i]=-1 — har element apne aap LIS of length 1
//   2) har j<i check karo: nums[j]<nums[i] ho to dp[i] improve + prev[i]=j set
//   3) bestLen/bestIdx track karo — sabse lamba ending index
//   4) prev chain se LIS reconstruct karo, reverse karke return
pair<int, vector<int>> lisWithPath(const vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
        return {0, {}};

    vector<int> dp(n, 1), prev(n, -1); // prev[i] = LIS me nums[i] se pehle ka index
    int bestLen = 1, bestIdx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j; // nums[i] ko nums[j] ke baad extend kiya
            }
        }
        if (dp[i] > bestLen) {
            bestLen = dp[i];
            bestIdx = i; // sabse lamba LIS yahan khatam hota hai
        }
    }

    vector<int> lis;
    for (int i = bestIdx; i != -1; i = prev[i]) // prev chain follow karke LIS banao
        lis.push_back(nums[i]);
    reverse(lis.begin(), lis.end());

    return {bestLen, lis};
}

// ── main: O(n^2) LIS length + sequence demo ─────────────────────────────────
//   1) sample array set karo, lisWithPath call karo
//   2) length aur actual LIS print karo
int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    auto [len, seq] = lisWithPath(nums);

    cout << "LIS length: " << len << "\nLIS: ";
    for (int x : seq)
        cout << x << " ";
    cout << endl;

    return 0;
}
