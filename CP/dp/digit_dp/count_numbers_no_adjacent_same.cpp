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

// ════════════════════════════════════════════════════════════════════════════
// NO ADJACENT SAME DIGITS — Digit DP
// ────────────────────────────────────────────────────────────────────────────
// State: pos, tight, prev (pichla digit; 10 = abhi koi prev nahi), started
// Memo: memo[pos][tight][prev][started]
// Constraint: started && d==prev -> skip (lagatar same digit allowed nahi)
// prev update: number start ho gaya ho to prev=d, warna 10 (no prev yet)
// Base case: pos==len -> started ? 1 : 0
// ════════════════════════════════════════════════════════════════════════════

string num;
long long memo[20][2][11][2]; // prev digit 0-9, 10 = no prev yet

// ── solve: adjacent equal digits ke bina [0, N] count karo ────────────────
//   1) pos==len -> started ho to valid number 1
//   2) memo check
//   3) limit = tight ? N[pos] : 9
//   4) started && d==prev -> continue (adjacent same banned)
//   5) nPrev/nStarted update, tight && d==limit se recurse
long long solve(int pos, int tight, int prev, int started) {
    if (pos == (int)num.size())
        return started ? 1 : 0;

    if (memo[pos][tight][prev][started] != -1)
        return memo[pos][tight][prev][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        if (started && d == prev)
            continue; // adjacent same digit logic: pichle digit jaisa mat lagao
        int nPrev = (started || d > 0) ? d : 10; // ab tak number start nahi -> prev=10
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
