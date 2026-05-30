/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_divisible_by_k.cpp
 * PROBLEM  : Count numbers in [0, N] divisible by K
 * APPROACH : Digit DP with remainder state + leading zero flag
 * COMPLEX  : Time: O(log N * K)  |  Space: O(log N * K)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string num;
int modK;
long long memo[20][2][2000][2];

long long solve(int pos, int tight, int rem, int started) {
    if (pos == (int)num.size())
        return (started && rem == 0) ? 1 : 0;

    if (memo[pos][tight][rem][started] != -1)
        return memo[pos][tight][rem][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        int nStarted = started || d > 0;
        int nRem = nStarted ? (rem * 10 + d) % modK : 0;
        int nTight = tight && (d == limit);
        ans += solve(pos + 1, nTight, nRem, nStarted);
    }
    return memo[pos][tight][rem][started] = ans;
}

long long countDivisible(long long n, int k) {
    num = to_string(n);
    modK = k;
    memset(memo, -1, sizeof(memo));
    return solve(0, 1, 0, 0);
}

int main() {
    long long n = 100;
    int k = 7;
    cout << "Count in [0," << n << "] divisible by " << k << " = "
         << countDivisible(n, k) << endl;
    return 0;
}
