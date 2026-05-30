/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : modular_inverse.cpp
 * PROBLEM  : Modular inverse a^(-1) mod p (p prime)
 * APPROACH : Fermat's little theorem — a^(p-2) mod p
 * COMPLEX  : Time: O(log p)  |  Space: O(1)
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

long long modInverseFermat(long long a, long long mod) {
    return modPow(a, mod - 2, mod);
}

int main() {
    long long mod = 1e9 + 7;
    long long a = 123456789;
    long long inv = modInverseFermat(a, mod);
    cout << "Inverse of " << a << " mod " << mod << " = " << inv << endl;
    cout << "Verify: " << (a * inv) % mod << endl;
    return 0;
}
