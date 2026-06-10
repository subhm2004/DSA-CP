/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : sieve_of_eratosthenes.cpp
 * PROBLEM  : Sieve Of Eratosthenes
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Sieve of Eratosthenes — mark multiples of primes.
 * COMPLEX  : Time: O(n log log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SIEVE OF ERATOSTHENES — 2 se n tak saare primes nikalo
// ────────────────────────────────────────────────────────────────────────────
// Funda: isPrime[i]=true se start — har prime ke multiples false karo
// i*i se start karo (chhote multiples pehle hi mark ho chuke)
// COMPLEX: Time O(n log log n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── sieveOfEratosthenes: boolean sieve se primes list banao ──────────────────
//   1) isPrime[0..n] sab true — 0,1 ko false (prime nahi)
//   2) i=2 se sqrt(n) — isPrime[i] true? multiples mark false
//   3) j = i*i se start — har j += i pe isPrime[j]=false
//   4) jo indices true bache — primes vector me daalo, return
vector<int> sieveOfEratosthenes(int n)
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false; // 0 aur 1 prime nahi hain

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false; // i ka multiple — composite
        }
    }

    for (int i = 2; i <= n; i++)
        if (isPrime[i])
            primes.push_back(i);

    return primes;
}

// ── main: user input pe sieve run karo ─────────────────────────────────────
//   1) n input lo
//   2) sieveOfEratosthenes call — primes print karo
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
