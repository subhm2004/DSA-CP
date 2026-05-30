/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : ncr_mod_p.cpp
 * PROBLEM  : nCr mod p using precomputed factorials (n, p <= 1e6, p prime)
 * APPROACH : fact[n] * invFact[r] * invFact[n-r] mod p
 * COMPLEX  : Precompute O(N), Query O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 200005;

long long fact[MAXN], invFact[MAXN];

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

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN - 1] = modPow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n)
        return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    precompute();
    cout << "C(10,3) mod 1e9+7 = " << nCr(10, 3) << endl;
    cout << "C(100000,50000) mod 1e9+7 = " << nCr(100000, 50000) << endl;
    return 0;
}
