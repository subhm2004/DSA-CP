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



/*
 * simpleSieve()
 * Purpose : Sieve of Eratosthenes — mark multiples of primes.
 * Params  : int limit
 * Returns : vector<int>
 */
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



/*
 * segmentedSieve()
 * Purpose : Sieve of Eratosthenes — mark multiples of primes.
 * Params  : int left, int right
 * Returns : vector<int>
 */
vector<int> segmentedSieve(int left, int right)
{
    if (left < 2)
        left = 2; // Prime numbers start from 2
    int limit = sqrt(right);

    vector<int> basePrimes = simpleSieve(limit);

    vector<bool> isPrime(right - left + 1, true);

    for (int prime : basePrimes)
    {
        int start = max(prime * prime, (left + prime - 1) / prime * prime);
        for (int j = start; j <= right; j += prime)
            isPrime[j - left] = false;
    }

    vector<int> primes;
    for (int i = 0; i < isPrime.size(); i++)
        if (isPrime[i])
            primes.push_back(left + i);

    return primes;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Segmented Sieve
 */
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
