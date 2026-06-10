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

// ════════════════════════════════════════════════════════════════════════════
// SUBSET SUM — Pick / Not Pick Recursion
// ────────────────────────────────────────────────────────────────────────────
// Har index par: element lo (target -= arr[idx]) ya chhod do (target same).
// Base: target == 0 -> true; target < 0 ya index over -> false.
// Pehle pick try karo, phir don't pick — koi bhi true ho to answer true.
// Complexity: O(2^n) time, O(n) recursion stack.
// ════════════════════════════════════════════════════════════════════════════

// ── subsetSumRec: recursive pick/not-pick subset sum ────────────────────────
//   1) target == 0 -> empty subset se match, true return
//   2) index khatam ya target negative -> false (impossible)
//   3) pick: arr[idx] lo, idx+1 par recurse with target - arr[idx]
//   4) don't pick: idx+1 par recurse with same target
bool subsetSumRec(vector<int> &arr, int idx, int target) {
    if (target == 0)
        return true;

    if (idx == (int)arr.size() || target < 0)
        return false;

    // pick arr[idx] — element include karo
    if (subsetSumRec(arr, idx + 1, target - arr[idx]))
        return true;

    // don't pick arr[idx] — element skip karo
    return subsetSumRec(arr, idx + 1, target);
}

// ── existsSubsetSum: wrapper — index 0 se recursion shuru ───────────────────
//   1) arr aur target pass karo, idx = 0 se subsetSumRec call karo
//   2) koi valid subset hai ya nahi return karo
bool existsSubsetSum(vector<int> &arr, int target) {
    return subsetSumRec(arr, 0, target);
}

// ── main: recursive subset sum demo ─────────────────────────────────────────
//   1) sample array {3,34,4,12,5,2}, target 9
//   2) existsSubsetSum print karo (true: 4+5)
int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << boolalpha;
    cout << "Subset with sum " << target << " exists: "
         << existsSubsetSum(arr, target) << endl; // true (4+5)

    return 0;
}
