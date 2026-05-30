/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_no_adjacent_same.cpp
 * PROBLEM  : Count numbers in [0, N] with no two adjacent equal digits
 * APPROACH : Digit DP — state includes previous digit
 * COMPLEX  : Time: O(log N * 10)  |  Space: O(log N * 10)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string num;
long long memo[20][2][11][2]; // prev digit 0-9, 10 = no prev yet

long long solve(int pos, int tight, int prev, int started) {
    if (pos == (int)num.size())
        return started ? 1 : 0;

    if (memo[pos][tight][prev][started] != -1)
        return memo[pos][tight][prev][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        if (started && d == prev)
            continue;
        int nPrev = (started || d > 0) ? d : 10;
        int nStarted = started || d > 0;
        ans += solve(pos + 1, tight && d == limit, nPrev, nStarted);
    }
    return memo[pos][tight][prev][started] = ans;
}

int main() {
    num = "1000";
    memset(memo, -1, sizeof(memo));
    cout << "Count in [0," << num << "] with no adjacent same digits = "
         << solve(0, 1, 10, 0) << endl;
    return 0;
}
