/*
 * ============================================================================
 * TOPIC    : Probability DP
 * FILE     : dice_roll_expectation.cpp
 * PROBLEM  : Expected rolls to reach target sum with n-sided die
 * APPROACH : dp[s] = expected rolls from sum s to reach target
 * COMPLEX  : Time: O(target * faces)  |  Space: O(target)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DICE ROLL EXPECTATION — Probability DP (Expected Value Recurrence)
// ────────────────────────────────────────────────────────────────────────────
// n-sided die se target sum tak pahunchne me kitne rolls lagenge — expected value.
// dp[s] = sum s se target tak pahunchne ke expected rolls.
// Base case: dp[target] = 0 — target pe already ho, aur roll nahi chahiye.
// Transition (backward): dp[s] = (1/n) * sum over faces of (1 + dp[s+face]).
//   Agar s+face > target (overshoot) to bhi 1 roll count hota hai, dp nahi badhta.
// Bottom-up: target-1 se 0 tak fill karo, answer = dp[0].
// Time: O(target * n)  |  Space: O(target)
// ════════════════════════════════════════════════════════════════════════════

// ── expectedRolls: target sum tak expected dice rolls nikalo ──────────────
//   1) dp[target] = 0 — base case, target pe koi aur roll nahi chahiye
//   2) s = target-1 se 0 tak backward iterate karo (smaller sums pe depend karta hai)
//   3) Har face 1..n ke liye: s+face <= target ho to 1+dp[s+face], warna sirf 1 (overshoot)
//   4) dp[s] = sum / n — har face equally likely hai, average le lo
//   5) dp[0] return karo — shuru se target tak expected rolls
double expectedRolls(int n, int target) {
    vector<double> dp(target + 1, 0.0);
    dp[target] = 0.0;

    for (int s = target - 1; s >= 0; s--) {
        double sum = 0;
        for (int face = 1; face <= n; face++) {
            if (s + face <= target)
                sum += 1.0 + dp[s + face];
            else
                sum += 1.0; // overshoot — still counts as one roll
        }
        dp[s] = sum / n;
    }
    return dp[0];
}

// ── main: sample die aur target pe expected rolls print karo ──────────────
//   1) 6-sided die, target sum 10 set karo
//   2) expectedRolls() call karke result 4 decimal places me print karo
int main() {
    int faces = 6, target = 10;
    cout << fixed << setprecision(4);
    cout << "Expected rolls (" << faces << "-sided die, target " << target
         << ") = " << expectedRolls(faces, target) << endl;
    return 0;
}
