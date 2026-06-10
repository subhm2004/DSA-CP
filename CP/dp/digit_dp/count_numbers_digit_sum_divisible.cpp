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

// ════════════════════════════════════════════════════════════════════════════
// DIGIT SUM DIVISIBLE BY K — Digit DP with modulo state
// ────────────────────────────────────────────────────────────────────────────
// State: pos, tight, sumMod (digit sum % K), started (leading zero?)
// Memo: memo[pos][tight][sumMod][started]
// Har digit pe sumMod = (sumMod + d) % modK update — modulo arithmetic
// started=0 pe sumMod 0 rehta (leading zeros count nahi)
// Base case: pos==len && started && sumMod==0 -> valid count 1
// ════════════════════════════════════════════════════════════════════════════

string num;
int modK;
long long memo[20][2][200][2];

// ── solve: digit sum % K == 0 wale numbers [0, N] me count karo ─────────────
//   1) pos == len -> started ho aur sumMod==0 ho to 1, warna 0
//   2) memo hit to cached return
//   3) limit = tight ? N[pos] : 9
//   4) nStarted = started || d>0; nSum = started ho to (sumMod+d)%modK
//   5) har allowed digit pe recurse, memo me store
long long solve(int pos, int tight, int sumMod, int started) {
    if (pos == (int)num.size())
        return (started && sumMod == 0) ? 1 : 0;

    if (memo[pos][tight][sumMod][started] != -1)
        return memo[pos][tight][sumMod][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        int nStarted = started || d > 0;
        int nSum = nStarted ? (sumMod + d) % modK : 0; // modulo: digit sum ka remainder track
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
