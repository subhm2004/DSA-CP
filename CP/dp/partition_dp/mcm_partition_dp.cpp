/*
 * ============================================================================
 * TOPIC    : Partition DP
 * FILE     : mcm_partition_dp.cpp
 * PROBLEM  : Matrix Chain Multiplication — minimum scalar multiplications
 * APPROACH : Partition DP — try every split k between i and j
 * COMPLEX  : Time: O(n^3)  |  Space: O(n^2)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MATRIX CHAIN MULTIPLICATION — Partition DP (Memoization)
// ────────────────────────────────────────────────────────────────────────────
// dims[i-1] x dims[i] = matrix i ki dimensions; chain A1..An multiply karo.
// dp[i][j] = matrices i se j multiply karne ka minimum scalar cost.
// Har split k try karo: pehle (i..k) aur (k+1..j) alag multiply, phir merge.
// Merge cost = dims[i-1] * dims[k] * dims[j]; base case i==j pe cost 0.
// ════════════════════════════════════════════════════════════════════════════

class MatrixChainMultiplication {
public:
    vector<vector<int>> dp;

    // ── solve: min cost for multiplying matrices i..j ───────────────────────
    //   1) base: i==j — ek matrix, multiply cost 0
    //   2) dp[i][j] cached ho to wahi return (memoization)
    //   3) har k in [i, j-1] pe chain ko do parts me todo
    //   4) cost = solve(i,k) + solve(k+1,j) + dims[i-1]*dims[k]*dims[j]
    //   5) sab splits me se minimum store karke dp[i][j] return karo
    int solve(int i, int j, const vector<int> &dims) {
        if (i == j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int mini = INT_MAX;

        for (int k = i; k < j; k++) {
            int cost = solve(i, k, dims) + solve(k + 1, j, dims)
                       + dims[i - 1] * dims[k] * dims[j];
            mini = min(mini, cost);
        }

        return dp[i][j] = mini;
    }

    // ── minCost: poori chain ka minimum multiplication cost ─────────────────
    //   1) n = dims.size(); dp table n x n, sab -1 (uncomputed)
    //   2) solve(1, n-1) call — matrix 1 se n-1 tak ki chain
    //   3) result = optimal parenthesization ka total scalar cost
    int minCost(const vector<int> &dims) {
        int n = dims.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(1, n - 1, dims);
    }
};

// ── main: sample dimensions par MCM cost print ────────────────────────────
//   dims = {10,20,30,40} — 3 matrices; minimum multiplications stdout par
int main() {
    vector<int> dims = {10, 20, 30, 40};
    MatrixChainMultiplication mcm;
    cout << "Minimum multiplications: " << mcm.minCost(dims) << endl;
    return 0;
}
