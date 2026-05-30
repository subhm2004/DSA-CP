/*
 * ============================================================================
 * TOPIC    : Subset Sum
 * FILE     : subset_sum_bitmask.cpp
 * PROBLEM  : Subset sum using bitmask enumeration (n <= 20 typical)
 * APPROACH : mask from 0 to 2^n - 1; bit i = include arr[i]
 * COMPLEX  : Time: O(2^n * n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool subsetSumBitmask(vector<int> &arr, int target) {
    int n = arr.size();
    int totalMasks = 1 << n;

    for (int mask = 0; mask < totalMasks; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                sum += arr[i];
        }
        if (sum == target)
            return true;
    }
    return false;
}

vector<vector<int>> allSubsetsWithSum(vector<int> &arr, int target) {
    int n = arr.size();
    vector<vector<int>> result;

    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        vector<int> subset;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
                subset.push_back(arr[i]);
            }
        }

        if (sum == target)
            result.push_back(subset);
    }
    return result;
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int target = 5;

    cout << boolalpha << "Exists (bitmask): " << subsetSumBitmask(arr, target) << endl;

    auto all = allSubsetsWithSum(arr, target);
    cout << "All subsets with sum " << target << ":\n";
    for (auto &s : all) {
        for (int x : s)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}
