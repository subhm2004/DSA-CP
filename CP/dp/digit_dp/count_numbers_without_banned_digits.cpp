/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_without_banned_digits.cpp
 * PROBLEM  : Count numbers in [0, N] that do not contain banned digit(s)
 * APPROACH : Digit DP — skip banned digits at each position
 * COMPLEX  : Time: O(log N * 10)  |  Space: O(log N)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string num;
bool banned[10];
long long memo[20][2][2];

long long solve(int pos, int tight, int started) {
    if (pos == (int)num.size())
        return started ? 1 : 0;

    if (memo[pos][tight][started] != -1)
        return memo[pos][tight][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        if (banned[d])
            continue;
        ans += solve(pos + 1, tight && d == limit, started || d > 0);
    }
    return memo[pos][tight][started] = ans;
}

int main() {
    num = "1000";
    memset(banned, 0, sizeof(banned));
    banned[4] = true; // no digit 4

    memset(memo, -1, sizeof(memo));
    cout << "Count in [0," << num << "] without digit 4 = "
         << solve(0, 1, 0) << endl;
    return 0;
}
