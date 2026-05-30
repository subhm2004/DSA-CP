/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : fast_exponentiation.cpp
 * PROBLEM  : Compute (a^b) mod m in O(log b)
 * APPROACH : Binary exponentiation
 * COMPLEX  : Time: O(log b)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long modPow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    cout << "2^10 mod 1e9+7 = " << modPow(2, 10, 1000000007) << endl;
    cout << "5^100 mod 13 = " << modPow(5, 100, 13) << endl;
    return 0;
}
