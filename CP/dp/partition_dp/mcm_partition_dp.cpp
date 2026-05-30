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

class MatrixChainMultiplication {
public:
    vector<vector<int>> dp;

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

    int minCost(const vector<int> &dims) {
        int n = dims.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(1, n - 1, dims);
    }
};

int main() {
    vector<int> dims = {10, 20, 30, 40};
    MatrixChainMultiplication mcm;
    cout << "Minimum multiplications: " << mcm.minCost(dims) << endl;
    return 0;
}
