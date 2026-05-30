/*
 * ============================================================================
 * TOPIC    : Combinatorics — Inclusion-Exclusion
 * FILE     : inclusion_exclusion.cpp
 * PROBLEM  : Count numbers in [1, N] divisible by at least one of given primes
 * APPROACH : Principle of Inclusion-Exclusion over subsets of divisors
 * COMPLEX  : Time: O(2^k * log N)  |  Space: O(k)
 * ============================================================================
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

long long countDivisibleByAny(long long n, const vector<int> &divisors) {
    int k = divisors.size();
    long long bad = 0;

    for (int mask = 1; mask < (1 << k); mask++) {
        long long lcm = 1;
        int bits = 0;
        bool overflow = false;

        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                bits++;
                if (lcm > n / divisors[i]) {
                    overflow = true;
                    break;
                }
                lcm = lcm * divisors[i] / gcdLong(lcm, divisors[i]);
            }
        }
        if (overflow)
            continue;

        if (bits % 2 == 1)
            bad += n / lcm;
        else
            bad -= n / lcm;
    }
    return bad;
}

int main() {
    long long n = 30;
    vector<int> divisors = {2, 3, 5};

    long long divisible = countDivisibleByAny(n, divisors);
    cout << "In [1, " << n << "], divisible by 2 or 3 or 5: " << divisible << endl;
    cout << "Not divisible by any: " << n - divisible << endl;
    return 0;
}
