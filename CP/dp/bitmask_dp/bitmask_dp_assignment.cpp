/*
 * ============================================================================
 * TOPIC    : Bitmask DP
 * FILE     : bitmask_dp_assignment.cpp
 * PROBLEM  : Assign n jobs to n workers — min total cost
 * APPROACH : dp[mask] = min cost when `mask` jobs are assigned
 * COMPLEX  : Time: O(n^2 * 2^n)  |  Space: O(2^n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BITMASK DP — Assignment Problem (Min Cost Job-Worker Matching)
// ────────────────────────────────────────────────────────────────────────────
// n jobs ko n workers ko assign karo — har worker ek hi job, min total cost.
// dp[mask] = jab `mask` bits set hain (assigned jobs ka set) tab tak ka min cost.
// mask me set bits count = kitne workers already assign ho chuke hain.
// Transition: current worker = popcount(mask), har unassigned job j try karo:
//   next = mask | (1<<j), dp[next] = min(dp[next], dp[mask] + cost[worker][j]).
// Base: dp[0] = 0 (koi job assign nahi). Answer: dp[(1<<n)-1] (sab jobs assigned).
// Time: O(n^2 * 2^n)  |  Space: O(2^n)
// ════════════════════════════════════════════════════════════════════════════

// ── minAssignment: workers ko jobs assign karke min total cost nikalo ─────
//   1) dp[0] = 0, baaki sab INF — empty assignment se shuru karo
//   2) Har mask iterate karo; worker = popcount(mask) = ab kaunsa worker assign hoga
//   3) Har unassigned job j (mask me bit set nahi): next mask banao, cost add karo
//   4) dp[next] = min(dp[next], dp[mask] + cost[worker][j]) — best assignment track karo
//   5) dp[(1<<n)-1] return karo — sab n jobs assign ho gaye, min cost
int minAssignment(const vector<vector<int>> &cost) {
    int n = cost.size();
    const int INF = 1e9;
    vector<int> dp(1 << n, INF);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == INF)
            continue;
        int worker = __builtin_popcount(mask);
        for (int job = 0; job < n; job++) {
            if (mask & (1 << job))
                continue;
            int next = mask | (1 << job);
            dp[next] = min(dp[next], dp[mask] + cost[worker][job]);
        }
    }

    return dp[(1 << n) - 1];
}

// ── main: sample cost matrix pe min assignment cost print karo ────────────
//   1) 4x4 cost matrix set karo (4 workers, 4 jobs)
//   2) minAssignment(cost) call karke minimum total assignment cost print karo
int main() {
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    cout << "Minimum assignment cost = " << minAssignment(cost) << endl;
    return 0;
}
