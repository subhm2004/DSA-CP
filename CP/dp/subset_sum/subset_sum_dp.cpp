/*
 * ============================================================================
 * TOPIC    : Subset Sum
 * FILE     : subset_sum_dp.cpp
 * PROBLEM  : Subset sum exists? (0/1 knapsack DP — same as partition subset)
 * APPROACH : dp[s] = true if sum s achievable using first i elements
 * COMPLEX  : Time: O(n * target)  |  Space: O(target)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool subsetSumDP(vector<int> &arr, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int x : arr) {
        for (int s = target; s >= x; s--) {
            if (dp[s - x])
                dp[s] = true;
        }
    }

    return dp[target];
}

int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << boolalpha << "Subset sum " << target << " (DP): "
         << subsetSumDP(arr, target) << endl;

    return 0;
}
