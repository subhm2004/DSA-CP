/*
 * ============================================================================
 * TOPIC    : Subset Sum
 * FILE     : subset_sum_backtracking.cpp
 * PROBLEM  : Find all subsets that sum to target (backtracking)
 * APPROACH : Include / exclude each element; backtrack after explore
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int> &arr, int idx, int currentSum, int target,
               vector<int> &path, vector<vector<int>> &result) {
    if (currentSum == target) {
        result.push_back(path);
        return;
    }

    if (idx == (int)arr.size() || currentSum > target)
        return;

    // Exclude arr[idx]
    backtrack(arr, idx + 1, currentSum, target, path, result);

    // Include arr[idx]
    path.push_back(arr[idx]);
    backtrack(arr, idx + 1, currentSum + arr[idx], target, path, result);
    path.pop_back(); // backtrack
}

vector<vector<int>> subsetsWithSum(vector<int> &arr, int target) {
    vector<vector<int>> result;
    vector<int> path;
    backtrack(arr, 0, 0, target, path, result);
    return result;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int target = 5;

    auto result = subsetsWithSum(arr, target);

    cout << "Subsets with sum " << target << ":\n";
    for (auto &subset : result) {
        for (int x : subset)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}
