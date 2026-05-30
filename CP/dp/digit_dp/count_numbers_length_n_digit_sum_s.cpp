/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_length_n_digit_sum_s.cpp
 * PROBLEM  : Count n-digit numbers (no leading zero) with digit sum = S
 * APPROACH : Digit DP with exact length and sum target
 * COMPLEX  : Time: O(n * S * 10)  |  Space: O(n * S)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long memo[105][1005][2];
int len, targetSum;

long long solve(int pos, int sum, int tight, const string &num) {
    if (pos == len)
        return sum == targetSum ? 1 : 0;
    if (sum > targetSum)
        return 0;

    if (memo[pos][sum][tight] != -1)
        return memo[pos][sum][tight];

    int start = (pos == 0) ? 1 : 0;
    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = start; d <= limit; d++)
        ans += solve(pos + 1, sum + d, tight && d == limit, num);

    return memo[pos][sum][tight] = ans;
}

long long countExactLengthSum(int n, int s) {
    len = n;
    targetSum = s;
    string num(n, '9');
    memset(memo, -1, sizeof(memo));
    return solve(0, 0, 0, num);
}

int main() {
    int n = 3, s = 6;
    cout << n << "-digit numbers with digit sum " << s << " = "
         << countExactLengthSum(n, s) << endl;
    return 0;
}
