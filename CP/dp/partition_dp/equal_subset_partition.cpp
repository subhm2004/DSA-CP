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

// ════════════════════════════════════════════════════════════════════════════
// EQUAL SUBSET PARTITION — 0-1 Knapsack / Partition DP
// ────────────────────────────────────────────────────────────────────────────
// Total sum odd ho to do equal subsets impossible — seedha false.
// Target = total/2; dp[s] = kya sum 's' kisi subset se ban sakta hai?
// Har element x ke liye: s se x tak reverse loop — dp[s] |= dp[s-x].
// Agar dp[target] true hai to array do equal parts me split ho sakta hai.
// ════════════════════════════════════════════════════════════════════════════

// ── canPartition: do equal-sum subsets possible? ──────────────────────────
//   1) total sum nikalo — odd ho to false (equal split impossible)
//   2) target = total/2; dp[0]=true (empty subset sum 0)
//   3) har x ke liye s = target se x tak reverse: dp[s] |= dp[s-x]
//   4) reverse loop same element do baar use hone se bachata hai (0-1 knapsack)
//   5) dp[target] return — true matlab equal partition exist karta hai
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

// ── main: do sample arrays par partition check ──────────────────────────────
//   1) {1,5,11,5} — true expected (1+5+5 = 11)
//   2) {1,2,3,5} — false expected (equal split nahi ho sakta)
int main() {
    vector<int> arr = {1, 5, 11, 5};
    cout << boolalpha << "Can partition equally: " << canPartition(arr) << endl; // true (1+5+5=11)

    vector<int> arr2 = {1, 2, 3, 5};
    cout << "Can partition equally: " << canPartition(arr2) << endl; // false

    return 0;
}
