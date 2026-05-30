/*
 * ============================================================================
 * TOPIC    : Number Theory — Miller-Rabin
 * FILE     : miller_rabin.cpp
 * PROBLEM  : Primality test for large numbers (up to 10^18)
 * APPROACH : Miller-Rabin with deterministic bases for 64-bit
 * COMPLEX  : O(k log^3 n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

ull modMul(ull a, ull b, ull mod) {
    return (unsigned __int128)a * b % mod;
}

ull modPow(ull a, ull b, ull mod) {
    ull res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = modMul(res, a, mod);
        a = modMul(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool millerTest(ull n, ull a) {
    if (a % n == 0) return true;
    ull d = n - 1;
    while (d % 2 == 0) {
        if (modPow(a, d, n) == n - 1) return true;
        d /= 2;
    }
    return modPow(a, d, n) == n - 1 || modPow(a, d, n) == 1;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (n % p == 0) return n == p;
    if (n < 41) return true;
    // Deterministic for 64-bit
    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})
        if (!millerTest(n, a)) return false;
    return true;
}

int main() {
    vector<ull> tests = {997, 1000000007, 1000000000000000009ULL};
    for (ull x : tests)
        cout << x << " is " << (isPrime(x) ? "prime" : "not prime") << endl;
    return 0;
}
