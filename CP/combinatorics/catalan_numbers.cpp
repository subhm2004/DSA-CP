/*
 * ============================================================================
 * TOPIC    : Combinatorics — Catalan Numbers
 * FILE     : catalan_numbers.cpp
 * PROBLEM  : nth Catalan number and classic applications
 * APPROACH : C_n = (2n)! / ((n+1)! n!)  OR  DP: C[i] = sum C[j]*C[i-1-j]
 * COMPLEX  : Time: O(n^2) DP  |  Space: O(n)
 * ============================================================================
 *
 * Applications:
 *   - Valid parentheses of length 2n
 *   - BSTs with n distinct keys
 *   - Triangulations of (n+2)-gon
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long catalanDP(int n) {
    vector<long long> c(n + 1, 0);
    c[0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            c[i] = (c[i] + c[j] * c[i - 1 - j]) % MOD;

    return c[n];
}

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long catalanFormula(int n, const vector<long long> &fact, const vector<long long> &invFact) {
    // C_n = C(2n, n) - C(2n, n-1) = fact[2n] * invFact[n] * invFact[n] * inv(n+1)
    return fact[2 * n] * invFact[n] % MOD * invFact[n] % MOD * modPow(n + 1, MOD - 2) % MOD;
}

int main() {
    int n = 5;
    cout << "Catalan C_" << n << " (DP) = " << catalanDP(n) << endl;

    // Valid parentheses count for n pairs = C_n
    cout << "Valid parentheses with " << n << " pairs = " << catalanDP(n) << endl;

    return 0;
}
