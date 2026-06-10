/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_product_digits_k.cpp
 * PROBLEM  : Count numbers in [0, N] with product of digits = K
 * APPROACH : Digit DP — product state (works when K is small)
 * COMPLEX  : Time: O(log N * K)  |  Space: O(log N * K)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIGIT PRODUCT = K — Digit DP
// ────────────────────────────────────────────────────────────────────────────
// State: pos, tight, prod (digits ka product), started
// Memo: memo[pos][tight][prod][started]
// Product update: d=0 -> prod=0; prod=0 -> prod=d; warna prod*=d
// Pruning: nProd > targetProd ho to skip (aage badhne ka fayda nahi)
// Base case: pos==len && started && prod==targetProd -> 1
// ════════════════════════════════════════════════════════════════════════════

string num;
int targetProd;
long long memo[20][2][2000][2];

// ── solve: digit product exactly K wale numbers count karo ──────────────────
//   1) pos == len -> started && prod==targetProd ho to 1
//   2) memo check, limit tight se decide
//   3) har digit d pe product update: 0 digit special case handle
//   4) nProd > targetProd -> continue (prune invalid branches)
//   5) tight transition: tight && d==limit
long long solve(int pos, int tight, int prod, int started) {
    if (pos == (int)num.size())
        return (started && prod == targetProd) ? 1 : 0;

    if (memo[pos][tight][prod][started] != -1)
        return memo[pos][tight][prod][started];

    int limit = tight ? num[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++) {
        int nStarted = started || d > 0;
        int nProd = prod;
        if (nStarted) {
            if (d == 0)
                nProd = 0; // 0 digit -> product 0 ho jata hai
            else if (prod == 0)
                nProd = d; // pehla non-zero digit
            else
                nProd = prod * d;
        }
        if (nProd > targetProd)
            continue; // target se bada product — is path ko kaat do
        ans += solve(pos + 1, tight && d == limit, nProd, nStarted);
    }
    return memo[pos][tight][prod][started] = ans;
}

int main() {
    num = "500";
    targetProd = 12;
    memset(memo, -1, sizeof(memo));
    cout << "Count in [0," << num << "] with digit product " << targetProd << " = "
         << solve(0, 1, 1, 0) << endl;
    return 0;
}
