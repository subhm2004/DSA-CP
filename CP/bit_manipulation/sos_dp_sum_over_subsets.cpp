/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — SOS DP
 * FILE     : sos_dp_sum_over_subsets.cpp
 * PROBLEM  : For each mask, sum f[sub] over all sub ⊆ mask
 * APPROACH : Sum Over Subsets DP — iterate bits, propagate sums
 * COMPLEX  : Time: O(n * 2^n)  |  Space: O(2^n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<long long> sosSumOverSubsets(const vector<long long> &f) {
    int n = __builtin_ctz(f.size()); // assume size = 2^n
    vector<long long> dp = f;

    for (int bit = 0; bit < n; bit++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << bit))
                dp[mask] += dp[mask ^ (1 << bit)];
        }
    }
    return dp;
}

int main() {
    // f[mask] = value assigned to subset `mask`
    int n = 3;
    vector<long long> f(1 << n);
    f[0b001] = 2;
    f[0b010] = 3;
    f[0b100] = 5;
    f[0b111] = 7;

    vector<long long> ans = sosSumOverSubsets(f);

    cout << "SOS DP — sum over all submasks:\n";
    for (int mask = 0; mask < (1 << n); mask++)
        cout << "mask " << bitset<3>(mask) << " -> " << ans[mask] << endl;

    return 0;
}
