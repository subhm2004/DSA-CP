/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_with_digit_sum.cpp
 * PROBLEM  : Count numbers in [0, N] whose digit sum equals K
 * APPROACH : Digit DP with states (index, tight, sum_so_far)
 * COMPLEX  : Time: O(log N * K)  |  Space: O(log N * K)
 * ============================================================================
 *
 * State:
 *   pos  — current digit index (processing from left)
 *   tight — still bounded by digits of N (leading constraint)
 *   sum  — digit sum built so far
 */

#include <bits/stdc++.h>
using namespace std;

string num;
int targetSum;
long long memo[20][2][1000]; // pos, tight, sum (K <= 999 for demo)

long long solve(int pos, int tight, int sum) {
    if (sum > targetSum)
        return 0;

    if (pos == (int)num.size())
        return sum == targetSum ? 1 : 0;

    if (memo[pos][tight][sum] != -1)
        return memo[pos][tight][sum];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        int nextTight = tight && (digit == limit);
        ans += solve(pos + 1, nextTight, sum + digit);
    }

    return memo[pos][tight][sum] = ans;
}

long long countInRange(long long n, int k) {
    num = to_string(n);
    targetSum = k;
    memset(memo, -1, sizeof(memo));
    return solve(0, 1, 0);
}

int main() {
    long long n;
    int k;
    cout << "Enter N and target digit sum K: ";
    cin >> n >> k;

    cout << "Count of numbers in [0, " << n << "] with digit sum " << k
         << " = " << countInRange(n, k) << endl;

    return 0;
}
