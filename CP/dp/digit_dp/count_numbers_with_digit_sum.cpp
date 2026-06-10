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

// ════════════════════════════════════════════════════════════════════════════
// COUNT NUMBERS WITH DIGIT SUM = K — Digit DP
// ────────────────────────────────────────────────────────────────────────────
// State: pos (kaunsa digit), tight (N se bound?), sum (ab tak ka digit sum)
// Memo: memo[pos][tight][sum] — har state ek baar compute
// Har position pe 0..limit digits try karo, sum update karo, tight transition
// Base case: pos == len -> sum == targetSum ho to 1, warna 0
// ════════════════════════════════════════════════════════════════════════════

string num;
int targetSum;
long long memo[20][2][1000]; // pos, tight, sum (K <= 999 for demo)

// ── solve: recursive digit DP — [0, N] me digit sum == K wale count karo ───
//   1) sum > targetSum -> invalid path, 0 return
//   2) pos == num.size() -> poora number ban gaya; sum match ho to 1
//   3) memo hit ho to cached answer return
//   4) tight=1 ho to limit = N ka current digit, warna 9 tak free
//   5) har digit pe nextTight = tight && (digit == limit), sum += digit
long long solve(int pos, int tight, int sum) {
    if (sum > targetSum)
        return 0;

    if (pos == (int)num.size())
        return sum == targetSum ? 1 : 0;

    if (memo[pos][tight][sum] != -1)
        return memo[pos][tight][sum];

    int limit = tight ? num[pos] - '0' : 9; // tight flag: N ke digit se upar nahi ja sakte
    long long ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        int nextTight = tight && (digit == limit); // ab bhi N se tight bound?
        ans += solve(pos + 1, nextTight, sum + digit);
    }

    return memo[pos][tight][sum] = ans;
}

// ── countInRange: N aur K set karke DP chalao ───────────────────────────────
//   1) N ko string me convert — left-to-right digit processing
//   2) targetSum = k, memo reset (-1)
//   3) pos=0, tight=1, sum=0 se solve call — [0, N] range cover
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
