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

string num;
int targetProd;
long long memo[20][2][2000][2];

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
                nProd = 0;
            else if (prod == 0)
                nProd = d;
            else
                nProd = prod * d;
        }
        if (nProd > targetProd)
            continue;
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
