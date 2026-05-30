/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : chinese_remainder_theorem.cpp
 * PROBLEM  : Solve x ≡ r[i] (mod m[i]) for pairwise coprime moduli
 * APPROACH : Garner / CRT construction
 * COMPLEX  : Time: O(k log M)  |  Space: O(k)
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

long long modInverse(long long a, long long mod) {
    long long x, y;
    extGcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

long long chineseRemainderTheorem(const vector<long long> &r, const vector<long long> &m) {
    long long M = 1;
    for (long long mi : m)
        M *= mi;

    long long x = 0;
    for (int i = 0; i < (int)m.size(); i++) {
        long long Mi = M / m[i];
        x = (x + r[i] * Mi % M * modInverse(Mi, m[i]) % M) % M;
    }
    return (x + M) % M;
}

int main() {
    vector<long long> r = {2, 3, 1};
    vector<long long> m = {3, 4, 5};
    long long ans = chineseRemainderTheorem(r, m);
    cout << "CRT solution x = " << ans << endl;
    return 0;
}
