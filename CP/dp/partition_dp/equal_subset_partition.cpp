/*
 * ============================================================================
 * TOPIC    : Partition DP
 * FILE     : equal_subset_partition.cpp
 * PROBLEM  : Can array be partitioned into two subsets with equal sum?
 * APPROACH : Partition DP / 0-1 knapsack — dp[sum] reachable?
 * COMPLEX  : Time: O(n * sum)  |  Space: O(sum)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool canPartition(vector<int> &arr) {
    int total = accumulate(arr.begin(), arr.end(), 0);
    if (total % 2 != 0)
        return false;

    int target = total / 2;
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
    vector<int> arr = {1, 5, 11, 5};
    cout << boolalpha << "Can partition equally: " << canPartition(arr) << endl; // true (1+5+5=11)

    vector<int> arr2 = {1, 2, 3, 5};
    cout << "Can partition equally: " << canPartition(arr2) << endl; // false

    return 0;
}
