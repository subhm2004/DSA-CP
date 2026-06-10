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

// ════════════════════════════════════════════════════════════════════════════
// COUNT DIVISIBLE BY K — Digit DP with remainder
// ────────────────────────────────────────────────────────────────────────────
// State: pos, tight, rem (number % K), started (leading zero flag)
// Memo: memo[pos][tight][rem][started]
// Rem update: nRem = (rem * 10 + d) % modK — classic modular digit building
// started=0 pe rem=0 (sirf leading zeros, number abhi start nahi hua)
// Base case: pos==len && started && rem==0 -> divisible, count 1
// ════════════════════════════════════════════════════════════════════════════

string num;
int modK;
long long memo[20][2][2000][2];

// ── solve: [0, N] me K se divisible numbers count karo ────────────────────
//   1) pos == len -> started && rem==0 ho to valid (divisible by K)
//   2) memo se cached answer
//   3) limit tight flag se: N ke digit se zyada nahi
//   4) har digit d: nRem = (rem*10 + d) % modK — modulo transition
//   5) nextTight = tight && (d == limit), recurse
long long solve(int pos, int tight, int rem, int started) {
    if (pos == (int)num.size())
        return (started && rem == 0) ? 1 : 0;

    if (memo[pos][tight][rem][started] != -1)
        return memo[pos][tight][rem][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        int nStarted = started || d > 0;
        int nRem = nStarted ? (rem * 10 + d) % modK : 0; // modulo: number % K track karo
        int nTight = tight && (d == limit); // tight transition
        ans += solve(pos + 1, nTight, nRem, nStarted);
    }
    return memo[pos][tight][rem][started] = ans;
}

// ── countDivisible: N aur K setup karke DP run karo ───────────────────────
//   1) N -> string, modK = k set
//   2) memo reset, pos=0, tight=1, rem=0, started=0 se solve
//   3) total count return
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
