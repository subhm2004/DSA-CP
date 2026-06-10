/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : segmented_sieve.cpp
 * PROBLEM  : Segmented Sieve
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Sieve of Eratosthenes — mark multiples of primes.
 * COMPLEX  : Time: O(n log log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SEGMENTED SIEVE — bade range [left, right] me primes nikalo
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehle sqrt(right) tak simple sieve — base primes lo
// Phir segment [left,right] me har base prime ke multiples mark karo
// COMPLEX: Time ~O((r-l) log log r + sqrt(r) log log sqrt(r))
// ════════════════════════════════════════════════════════════════════════════

// ── simpleSieve: 2 se limit tak saare primes nikalo ────────────────────────
//   1) isPrime array banao, i=2 se limit traverse
//   2) prime mila? primes me push + multiples false mark from i*i
//   3) primes vector return — base primes for segment
vector<int> simpleSieve(int limit)
{
    vector<bool> isPrime(limit + 1, true);
    vector<int> primes;

    for (int i = 2; i <= limit; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
        }
    }
    return primes;
}

// ── segmentedSieve: range [left, right] ke primes nikalo ───────────────────
//   1) left < 2? left=2 set karo
//   2) simpleSieve(sqrt(right)) se base primes lo
//   3) segment-sized isPrime array — har prime se multiples mark
//   4) start = max(p*p, ceil(left/p)*p) — segment me pehla multiple
//   5) true indices ko left+i me convert karke return
vector<int> segmentedSieve(int left, int right)
{
    if (left < 2)
        left = 2; // primes 2 se shuru
    int limit = sqrt(right);

    vector<int> basePrimes = simpleSieve(limit);

    vector<bool> isPrime(right - left + 1, true); // segment array

    for (int prime : basePrimes)
    {
        int start = max(prime * prime, (left + prime - 1) / prime * prime);
        for (int j = start; j <= right; j += prime)
            isPrime[j - left] = false; // segment index me mark
    }

    vector<int> primes;
    for (int i = 0; i < isPrime.size(); i++)
        if (isPrime[i])
            primes.push_back(left + i); // actual number restore

    return primes;
}

// ── main: range input, segmented sieve run ───────────────────────────────────
//   1) left, right cin se lo
//   2) segmentedSieve call, primes print
int main()
{
    int left, right;
    cout << "Enter range (left right): ";
    cin >> left >> right;

    vector<int> primes = segmentedSieve(left, right);

    cout << "Prime numbers in range [" << left << ", " << right << "]:\n";
    for (int prime : primes)
        cout << prime << " ";
    cout << endl;

    return 0;
}
