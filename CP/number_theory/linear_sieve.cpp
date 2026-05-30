/*
 * ============================================================================
 * TOPIC    : Number Theory
 * FILE     : linear_sieve.cpp
 * PROBLEM  : Smallest prime factor (SPF) for every number up to N
 * APPROACH : Linear sieve — each composite crossed once by its smallest prime
 * COMPLEX  : Time: O(N)  |  Space: O(N)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> linearSieve(int n) {
    vector<int> spf(n + 1, 0), primes;
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || (long long)i * p > n)
                break;
            spf[i * p] = p;
        }
    }
    return spf;
}

vector<pair<int, int>> factorize(int x, const vector<int> &spf) {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0)
            x /= p, cnt++;
        factors.push_back({p, cnt});
    }
    return factors;
}

int main() {
    int n = 100;
    vector<int> spf = linearSieve(n);

    cout << "Primes up to " << n << ": ";
    for (int i = 2; i <= n; i++)
        if (spf[i] == i)
            cout << i << " ";
    cout << endl;

    int x = 84;
    cout << "Factorization of " << x << ": ";
    for (auto [p, c] : factorize(x, spf))
        cout << p << "^" << c << " ";
    cout << endl;
    return 0;
}
