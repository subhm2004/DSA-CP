/*
 * ============================================================================
 * TOPIC    : Interval DP
 * FILE     : optimal_bst.cpp
 * PROBLEM  : Optimal Binary Search Tree — minimum expected search cost
 * APPROACH : dp[i][j] = min cost for keys i..j, try root k in [i,j]
 * COMPLEX  : Time: O(n^3)  |  Space: O(n^2)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// OPTIMAL BINARY SEARCH TREE — Interval DP
// ────────────────────────────────────────────────────────────────────────────
// Keys 0..n-1 ki search frequencies di hain — BST banao min expected cost ke liye.
// dp[i][j] = keys i se j tak ka optimal BST banane ka minimum search cost.
// Har interval me root r try karo (i <= r <= j) — left/right subtrees alag solve.
// Cost = dp[i][r-1] + dp[r+1][j] + sum(freq[i..j]) — root depth 0, baaki +1 depth.
// prefix sum se rangeSum fast; len 1 pe base dp[i][i] = freq[i].
// ════════════════════════════════════════════════════════════════════════════

// ── optimalBST: minimum expected search cost for optimal BST ─────────────
//   1) prefix array se sum(i,j) = freq[i..j] ka total — har level pe add hoga
//   2) base: dp[i][i] = freq[i] — single key, cost = uski frequency
//   3) len 2 se n tak intervals badhao — har (i,j) ke liye root r try karo
//   4) left = dp[i][r-1], right = dp[r+1][j]; dp[i][j] = min(left+right+rangeSum)
//   5) dp[0][n-1] return — poori key range ka optimal BST minimum cost
int optimalBST(const vector<int> &freq) {
    int n = freq.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + freq[i];

    auto sum = [&](int i, int j) { return prefix[j + 1] - prefix[i]; };

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        dp[i][i] = freq[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            int rangeSum = sum(i, j);

            for (int r = i; r <= j; r++) {
                int left = (r > i) ? dp[i][r - 1] : 0;
                int right = (r < j) ? dp[r + 1][j] : 0;
                dp[i][j] = min(dp[i][j], left + right + rangeSum);
            }
        }
    }
    return dp[0][n - 1];
}

// ── main: sample frequencies par optimal BST cost print ───────────────────
//   freq = {4,2,6,3,1,2,5} — optimalBST call karke min cost stdout par
int main() {
    vector<int> freq = {4, 2, 6, 3, 1, 2, 5};
    cout << "Optimal BST min cost = " << optimalBST(freq) << endl;
    return 0;
}
