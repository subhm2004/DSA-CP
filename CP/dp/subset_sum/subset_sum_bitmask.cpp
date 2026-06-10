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

// ════════════════════════════════════════════════════════════════════════════
// SUBSET SUM — Bitmask Enumeration
// ────────────────────────────────────────────────────────────────────────────
// Har mask (0 se 2^n-1) ek unique subset represent karta hai.
// Bit i set hai -> arr[i] include; unset -> exclude.
// Har mask ka sum nikal ke target se compare karo.
// Complexity: O(2^n * n) time — chhote n (<=20) ke liye practical.
// ════════════════════════════════════════════════════════════════════════════

// ── subsetSumBitmask: koi subset target sum banata hai? ───────────────────────
//   1) har mask 0 se 2^n-1 tak iterate karo
//   2) har bit i check karo — set ho to arr[i] sum me add karo
//   3) sum == target -> turant true return
//   4) koi mask match na kare -> false
bool subsetSumBitmask(vector<int> &arr, int target) {
    int n = arr.size();
    int totalMasks = 1 << n;

    for (int mask = 0; mask < totalMasks; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) // bit i set = arr[i] is subset me hai
                sum += arr[i];
        }
        if (sum == target)
            return true;
    }
    return false;
}

// ── allSubsetsWithSum: saari subsets jinka sum == target ────────────────────
//   1) har mask ke liye sum aur subset vector banao
//   2) set bits wale elements subset me push karo
//   3) sum == target ho to result me daalo
//   4) saari matching subsets return karo
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

// ── main: bitmask subset sum demo ───────────────────────────────────────────
//   1) exists check aur saari subsets dono print karo
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
