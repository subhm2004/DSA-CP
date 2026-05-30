/*
 * ============================================================================
 * TOPIC    : Combinatorics — Burnside's Lemma
 * FILE     : burnside_lemma_coloring.cpp
 * PROBLEM  : Number of distinct necklaces with n beads and k colors
 * APPROACH : Burnside: |X/G| = (1/|G|) * sum of fixed colorings under each rotation
 * COMPLEX  : Time: O(n * k)  |  Space: O(1)
 * ============================================================================
 *
 * For rotation group of n beads:
 *   Fixed under rotation by d positions = k^gcd(n, d)
 */

#include <bits/stdc++.h>
using namespace std;

long long gcdLong(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

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

long long modInv(long long a, long long mod) {
    return modPow(a, mod - 2, mod);
}

long long necklaceColorings(int n, int k, long long mod = 1e9 + 7) {
    long long sum = 0;
    for (int d = 0; d < n; d++)
        sum = (sum + modPow(k, (int)gcdLong(n, d), mod)) % mod;
    return sum * modInv(n, mod) % mod;
}

int main() {
    int n = 4, k = 3; // 4 beads, 3 colors
    cout << "Distinct necklaces (n=" << n << ", k=" << k << ") = "
         << necklaceColorings(n, k) << endl;
    return 0;
}
