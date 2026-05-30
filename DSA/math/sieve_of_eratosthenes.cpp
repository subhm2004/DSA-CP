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



/*
 * sieveOfEratosthenes()
 * Purpose : Sieve of Eratosthenes — mark multiples of primes.
 * Params  : int n
 * Returns : vector<int>
 */
vector<int> sieveOfEratosthenes(int n)
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers

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



/*
 * main()
 * Purpose : Entry point — demo/test for Sieve Of Eratosthenes
 */
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
