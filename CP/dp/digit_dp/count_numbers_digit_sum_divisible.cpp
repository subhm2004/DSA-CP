/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_digit_sum_divisible.cpp
 * PROBLEM  : Count numbers in [0, N] whose digit sum is divisible by K
 * APPROACH : Digit DP — track digit sum mod K
 * COMPLEX  : Time: O(log N * K)  |  Space: O(log N * K)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string num;
int modK;
long long memo[20][2][200][2];

long long solve(int pos, int tight, int sumMod, int started) {
    if (pos == (int)num.size())
        return (started && sumMod == 0) ? 1 : 0;

    if (memo[pos][tight][sumMod][started] != -1)
        return memo[pos][tight][sumMod][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        int nStarted = started || d > 0;
        int nSum = nStarted ? (sumMod + d) % modK : 0;
        ans += solve(pos + 1, tight && d == limit, nSum, nStarted);
    }
    return memo[pos][tight][sumMod][started] = ans;
}

int main() {
    num = "1000";
    modK = 3;
    memset(memo, -1, sizeof(memo));
    cout << "Count with digit sum % " << modK << " == 0 in [0," << num << "] = "
         << solve(0, 1, 0, 0) << endl;
    return 0;
}
