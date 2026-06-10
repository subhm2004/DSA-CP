/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : prime_number_2.cpp
 * PROBLEM  : Prime Number 2
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Sieve of Eratosthenes — mark multiples of primes.
 * COMPLEX  : Time: O(n log log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SIEVE OF ERATOSTHENES — primes up to n (alternate implementation)
// ────────────────────────────────────────────────────────────────────────────
// Funda: boolean array me multiples mark — true wale prime hain
// i*i optimization — chhote multiples pehle hi cross ho chuke
// COMPLEX: Time O(n log log n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── sieveOfEratosthenes: n tak saare primes return karo ────────────────────
//   1) isPrime[0..n] true — 0,1 ko false mark
//   2) i=2 se i*i<=n — prime ke multiples false from i*i
//   3) true indices collect karke primes vector return
vector<int> sieveOfEratosthenes(int n)
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false; // 0 aur 1 prime nahi

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 2; i <= n; i++)
        if (isPrime[i])
            primes.push_back(i);

    return primes;
}

// ── main: user input pe primes print ─────────────────────────────────────────
//   1) n input, sieve run, primes list print
int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    vector<int> primes = sieveOfEratosthenes(n);

    cout << "Prime numbers up to " << n << ":\n";
    for (int prime : primes)
        cout << prime << " ";
    cout << endl;

    return 0;
}
