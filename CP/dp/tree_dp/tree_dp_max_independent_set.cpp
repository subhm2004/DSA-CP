/*
 * ============================================================================
 * TOPIC    : Tree DP
 * FILE     : tree_dp_max_independent_set.cpp
 * PROBLEM  : Maximum weight independent set on a tree
 * APPROACH : Tree DP — take node vs skip node
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TREE DP — Maximum Weight Independent Set on a Tree
// ────────────────────────────────────────────────────────────────────────────
// Independent set = koi do adjacent nodes dono select nahi ho sakte.
// Har node u pe do states: dp[u][0] = u skip karo, dp[u][1] = u select karo.
// Agar u select kiya to children skip karne padenge → dp[u][1] += dp[v][0].
// Agar u skip kiya to har child v pe max(dp[v][0], dp[v][1]) le sakte ho.
// DFS post-order: pehle children solve karo, phir parent combine karo.
// Answer = max(dp[root][0], dp[root][1]) — root select ya skip.
// Time: O(n)  |  Space: O(n)
// ════════════════════════════════════════════════════════════════════════════

vector<vector<int>> adj;
vector<int> weight;
vector<vector<long long>> dp;

// ── dfs: node u pe tree DP states compute karo (post-order) ───────────────
//   1) dp[u][0] = 0 (skip u), dp[u][1] = weight[u] (u select karo — apna weight add)
//   2) Har child v ke liye (parent skip karo): pehle dfs(v, u) — children solve karo
//   3) u skip case: dp[u][0] += max(dp[v][0], dp[v][1]) — child select ya skip, best lo
//   4) u select case: dp[u][1] += dp[v][0] — child ko skip karna zaroori (adjacent conflict)
void dfs(int u, int parent) {
    dp[u][0] = 0;              // skip u
    dp[u][1] = weight[u];      // take u

    for (int v : adj[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

// ── maxIndependentSet: tree ka max weight independent set nikalo ──────────
//   1) dp array n x 2 se initialize karo (har node ke liye 2 states)
//   2) root (0) se dfs(0, -1) chalao — poora tree bottom-up process hoga
//   3) max(dp[0][0], dp[0][1]) return karo — root select ya skip, jo zyada weight de
long long maxIndependentSet(int n) {
    dp.assign(n, vector<long long>(2, 0));
    dfs(0, -1);
    return max(dp[0][0], dp[0][1]);
}

// ── main: sample tree pe max independent set weight print karo ────────────
//   1) 5-node tree build karo: edges 0-1, 0-2, 1-3, 1-4 aur weights assign karo
//   2) maxIndependentSet(n) call karke maximum weight print karo
int main() {
    // Tree: 0-1, 0-2, 1-3, 1-4
    int n = 5;
    adj.assign(n, {});
    weight = {5, 1, 2, 8, 9};

    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1};

    cout << "Max independent set weight = " << maxIndependentSet(n) << endl;
    return 0;
}
