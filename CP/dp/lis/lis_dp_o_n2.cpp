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

pair<int, vector<int>> lisWithPath(const vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
        return {0, {}};

    vector<int> dp(n, 1), prev(n, -1);
    int bestLen = 1, bestIdx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > bestLen) {
            bestLen = dp[i];
            bestIdx = i;
        }
    }

    vector<int> lis;
    for (int i = bestIdx; i != -1; i = prev[i])
        lis.push_back(nums[i]);
    reverse(lis.begin(), lis.end());

    return {bestLen, lis};
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    auto [len, seq] = lisWithPath(nums);

    cout << "LIS length: " << len << "\nLIS: ";
    for (int x : seq)
        cout << x << " ";
    cout << endl;

    return 0;
}
