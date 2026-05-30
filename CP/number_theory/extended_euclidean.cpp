/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : extended_euclidean.cpp
 * PROBLEM  : Find x, y such that a*x + b*y = gcd(a,b); modular inverse for coprime a,m
 * APPROACH : Extended Euclidean algorithm
 * COMPLEX  : Time: O(log min(a,b))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

long long extGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modInverseExtended(long long a, long long mod) {
    long long x, y;
    long long g = extGcd(a, mod, x, y);
    if (g != 1)
        return -1;
    return (x % mod + mod) % mod;
}

int main() {
    long long a = 17, b = 13;
    long long x, y;
    long long g = extGcd(a, b, x, y);
    cout << g << " = " << a << "*" << x << " + " << b << "*" << y << endl;

    long long mod = 1e9 + 7;
    cout << "Inverse of 100000007 mod 1e9+7 = " << modInverseExtended(100000007, mod) << endl;
    return 0;
}
