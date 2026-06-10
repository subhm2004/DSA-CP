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

// ════════════════════════════════════════════════════════════════════════════
// COUNT WITHOUT BANNED DIGITS — Digit DP
// ────────────────────────────────────────────────────────────────────────────
// State: pos, tight (N bound), started (leading zero abhi tak?)
// Memo: memo[pos][tight][started]
// Banned digits loop me skip — sirf allowed digits try karo
// started=0 pe sirf 0 allowed (leading zeros); started=1 pe valid number count
// Base case: pos == len -> started ho to 1 (valid number), warna 0
// ════════════════════════════════════════════════════════════════════════════

string num;
bool banned[10];
long long memo[20][2][2];

// ── solve: [0, N] me banned digit na ho aise numbers count karo ─────────────
//   1) pos == len -> number complete; started=1 ho to valid count 1
//   2) memo check — pehle compute ho chuka to return
//   3) tight=1 ho to limit = N ka digit, warna 0..9
//   4) banned[d] true ho to skip — ye digit use nahi kar sakte
//   5) nextTight = tight && d==limit, started = started || d>0
long long solve(int pos, int tight, int started) {
    if (pos == (int)num.size())
        return started ? 1 : 0;

    if (memo[pos][tight][started] != -1)
        return memo[pos][tight][started];

    int limit = tight ? num[pos] - '0' : 9; // tight flag se upper bound
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        if (banned[d])
            continue; // banned digit logic: is digit wale paths invalid
        ans += solve(pos + 1, tight && d == limit, started || d > 0);
    }
    return memo[pos][tight][started] = ans;
}

int main() {
    num = "1000";
    memset(banned, 0, sizeof(banned));
    banned[4] = true; // digit 4 banned — koi bhi number me 4 nahi aana chahiye

    memset(memo, -1, sizeof(memo));
    cout << "Count in [0," << num << "] without digit 4 = "
         << solve(0, 1, 0) << endl;
    return 0;
}
