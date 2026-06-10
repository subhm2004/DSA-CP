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

// ════════════════════════════════════════════════════════════════════════════
// EXACT LENGTH N, DIGIT SUM S — Digit DP (no leading zero)
// ────────────────────────────────────────────────────────────────────────────
// State: pos, sum (ab tak ka digit sum), tight (upper bound "999..9" se?)
// Memo: memo[pos][sum][tight]
// pos==0 pe start=1 (leading zero forbidden — n-digit number chahiye)
// Upper bound: num = "999...9" (n times) — tight usually 0 (free digits)
// Base case: pos==len -> sum==targetSum ho to 1
// ════════════════════════════════════════════════════════════════════════════

long long memo[105][1005][2];
int len, targetSum;

// ── solve: exactly n digits, digit sum = S, no leading zero ───────────────
//   1) pos==len -> sum==targetSum ? 1 : 0
//   2) sum > targetSum -> prune, 0 return
//   3) memo hit to return cached
//   4) start = (pos==0) ? 1 : 0 — pehla digit 0 nahi ho sakta
//   5) limit tight se; har d pe sum+d, tight && d==limit
long long solve(int pos, int sum, int tight, const string &num) {
    if (pos == len)
        return sum == targetSum ? 1 : 0;
    if (sum > targetSum)
        return 0;

    if (memo[pos][sum][tight] != -1)
        return memo[pos][sum][tight];

    int start = (pos == 0) ? 1 : 0; // leading zero rule: pehli position 1-9 hi
    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = start; d <= limit; d++)
        ans += solve(pos + 1, sum + d, tight && d == limit, num);

    return memo[pos][sum][tight] = ans;
}

// ── countExactLengthSum: n-digit numbers with sum S count karo ─────────────
//   1) len=n, targetSum=s set
//   2) upper bound string = n copies of '9'
//   3) memo reset, tight=0 (999..9 se loosely bound — mostly free)
//   4) solve(0, 0, 0, num) return
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
