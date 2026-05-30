/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : lucas_theorem.cpp
 * PROBLEM  : nCr mod p where p is prime and n can be very large
 * APPROACH : Lucas theorem — break n, r in base p
 * COMPLEX  : Time: O(p log_p n) per query
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long modPow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long smallNcr(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    long long num = 1, den = 1;
    for (long long i = 0; i < r; i++) {
        num = num * ((n - i) % p) % p;
        den = den * ((i + 1) % p) % p;
    }
    return num * modPow(den, p - 2, p) % p;
}

long long lucasNcr(long long n, long long r, long long p) {
    if (r == 0)
        return 1;
    return lucasNcr(n / p, r / p, p) * smallNcr(n % p, r % p, p) % p;
}

int main() {
    long long n = 1000000000000LL, r = 500000000000LL, p = 1000000007;
    cout << "Lucas C(" << n << "," << r << ") mod " << p << " = "
         << lucasNcr(n, r, p) << endl;
    return 0;
}
