/*
 * ============================================================================
 * TOPIC    : Subset Sum
 * FILE     : subset_sum_recursion.cpp
 * PROBLEM  : Does any subset sum to target? (pick / not pick recursion)
 * APPROACH : At each index: skip element OR take element
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool subsetSumRec(vector<int> &arr, int idx, int target) {
    if (target == 0)
        return true;

    if (idx == (int)arr.size() || target < 0)
        return false;

    // Pick arr[idx]
    if (subsetSumRec(arr, idx + 1, target - arr[idx]))
        return true;

    // Don't pick arr[idx]
    return subsetSumRec(arr, idx + 1, target);
}

bool existsSubsetSum(vector<int> &arr, int target) {
    return subsetSumRec(arr, 0, target);
}

int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << boolalpha;
    cout << "Subset with sum " << target << " exists: "
         << existsSubsetSum(arr, target) << endl; // true (4+5)

    return 0;
}
