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

// ════════════════════════════════════════════════════════════════════════════
// SUBSET SUM — Backtracking (All Subsets)
// ────────────────────────────────────────────────────────────────────────────
// Har index par do choices: element include karo ya exclude karo.
// currentSum == target -> valid subset mil gaya, path ko result me daalo.
// Pruning: currentSum > target ya index khatam -> return (aage mat jao).
// Complexity: O(2^n) time (sab subsets explore), O(n) recursion depth.
// ════════════════════════════════════════════════════════════════════════════

// ── backtrack: include/exclude se saari valid subsets dhoondo ───────────────
//   1) currentSum == target -> path ko result me save karo, return
//   2) base case: index over ya sum > target -> return (dead end)
//   3) pehle exclude: idx+1 par jao bina element liye
//   4) phir include: path me daalo, recurse, phir pop_back (backtrack)
void backtrack(vector<int> &arr, int idx, int currentSum, int target,
               vector<int> &path, vector<vector<int>> &result) {
    if (currentSum == target) {
        result.push_back(path);
        return;
    }

    if (idx == (int)arr.size() || currentSum > target)
        return;

    // exclude arr[idx] — is element ko skip karo
    backtrack(arr, idx + 1, currentSum, target, path, result);

    // include arr[idx] — lo, explore karo, phir undo
    path.push_back(arr[idx]);
    backtrack(arr, idx + 1, currentSum + arr[idx], target, path, result);
    path.pop_back(); // backtrack — path ko original state me lao
}

// ── subsetsWithSum: wrapper — saari subsets with given sum ──────────────────
//   1) empty result aur path banao
//   2) index 0, sum 0 se backtrack shuru karo
//   3) poori result list return karo
vector<vector<int>> subsetsWithSum(vector<int> &arr, int target) {
    vector<vector<int>> result;
    vector<int> path;
    backtrack(arr, 0, 0, target, path, result);
    return result;
}

// ── main: sample backtracking subset sum ────────────────────────────────────
//   1) arr aur target set karo, subsetsWithSum call karo
//   2) har valid subset print karo
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
