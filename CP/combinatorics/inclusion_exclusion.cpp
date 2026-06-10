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

// ════════════════════════════════════════════════════════════════════════════
// INCLUSION-EXCLUSION PRINCIPLE (PIE)
// ────────────────────────────────────────────────────────────────────────────
// [1..n] me kam se kam ek divisor se divisible count:
//   |A₁ ∪ A₂ ∪ ...| = Σ|A_i| - Σ|A_i∩A_j| + Σ|A_i∩A_j∩A_k| - ...
// Implementation: har non-empty subset (mask) ka LCM lo → n/lcm add/sub
// Odd bits → add (+), even bits → subtract (-)
// COMPLEX: O(2^k * k)  — k ≤ 20 usually
// ════════════════════════════════════════════════════════════════════════════

long long gcdLong(long long a, long long b)
{
    a = llabs(a);
    b = llabs(b);
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

// ── countDivisibleByAny: [1,n] me kisi bhi divisor se divisible kitne ──
//   1) har mask = 1 .. 2^k-1 (non-empty subset of divisors)
//   2) mask ke set bits ka LCM nikalo (overflow check)
//   3) count = n / lcm — kitne multiples
//   4) odd |mask| → bad += count, even → bad -= count
//   Answer = bad (at least one divisor se divisible)
long long countDivisibleByAny(long long n, const vector<int> &divisors)
{
    int k = divisors.size();
    long long bad = 0;

    for (int mask = 1; mask < (1 << k); mask++)
    {
        long long lcm = 1;
        int bits = 0;
        bool overflow = false;

        for (int i = 0; i < k; i++)
        {
            if (mask & (1 << i))
            {
                bits++;
                if (lcm > n / divisors[i]) // lcm * d > n → sab multiples 0
                {
                    overflow = true;
                    break;
                }
                lcm = lcm * divisors[i] / gcdLong(lcm, divisors[i]);
            }
        }
        if (overflow)
            continue;

        if (bits % 2 == 1)
            bad += n / lcm; // single/subset with odd size → add
        else
            bad -= n / lcm; // even size intersection → subtract (double count fix)
    }
    return bad;
}

int main()
{
    long long n = 30;
    vector<int> divisors = {2, 3, 5};

    long long divisible = countDivisibleByAny(n, divisors);
    cout << "In [1, " << n << "], divisible by 2 or 3 or 5: " << divisible << endl;
    cout << "Not divisible by any: " << n - divisible << endl;
    return 0;
}
