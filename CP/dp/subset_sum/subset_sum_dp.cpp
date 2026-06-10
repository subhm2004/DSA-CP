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

// ════════════════════════════════════════════════════════════════════════════
// SUBSET SUM — 0/1 Knapsack Style DP
// ────────────────────────────────────────────────────────────────────────────
// State: dp[s] = true agar sum s pehle processed elements se ban sakta hai.
// Transition: element x lo -> dp[s] |= dp[s-x] (x ko include karo).
// Reverse loop (s = target se x tak) — 0/1 constraint, ek element ek baar.
// Complexity: O(n * target) time, O(target) space.
// ════════════════════════════════════════════════════════════════════════════

// ── subsetSumDP: kya koi subset target sum banata hai? ──────────────────────
//   1) dp[0] = true — empty subset se sum 0 possible
//   2) har element x ke liye s ko target se reverse me update karo
//   3) agar dp[s-x] true hai -> dp[s] = true (x include karke s banao)
//   4) dp[target] return — target achievable hai ya nahi
bool subsetSumDP(vector<int> &arr, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int x : arr) {
        // reverse loop: x ko is iteration me sirf ek baar use karo
        for (int s = target; s >= x; s--) {
            if (dp[s - x])
                dp[s] = true;
        }
    }

    return dp[target];
}

// ── main: DP subset sum existence check ─────────────────────────────────────
//   1) sample array aur target set karo
//   2) subsetSumDP result print karo (e.g. 4+5 = 9)
int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << boolalpha << "Subset sum " << target << " (DP): "
         << subsetSumDP(arr, target) << endl;

    return 0;
}
