#include <bits/stdc++.h>
using namespace std;

// ✅ Standard Sieve of Eratosthenes to Find Small Primes up to `sqrt(high)`
vector<int> sieveOfEratosthenes(int N)
{
    vector<bool> isPrime(N + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false; // 0 & 1 are not primes

    for (int i = 2; i * i <= N; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    // Store primes found
    for (int i = 2; i <= N; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}

// ✅ Segmented Sieve to Find Primes in Range [low, high]
vector<int> segmentedSieve(int low, int high)
{
    int limit = sqrt(high) + 1;
    vector<int> smallPrimes = sieveOfEratosthenes(limit); // Get small primes ≤ sqrt(high)

    vector<bool> isPrime(high - low + 1, true); // Boolean array for [low, high]

    // Mark non-primes using small primes
    for (int prime : smallPrimes)
    {
        int start = max(prime * prime, (low + prime - 1) / prime * prime); // Find first multiple

        for (int j = start; j <= high; j += prime)
        {
            isPrime[j - low] = false;
        }
    }

    // Collect primes in range [low, high]
    vector<int> primes;
    for (int i = low; i <= high; ++i)
    {
        if (isPrime[i - low] && i > 1)
        { // Ignore 1 (not prime)
            primes.push_back(i);
        }
    }

    return primes;
}

// ✅ Main Function
int main()
{
    int low, high;
    cout << "Enter range [low high]: ";
    cin >> low >> high;

    vector<int> primes = segmentedSieve(low, high);
    cout << "Primes in range [" << low << ", " << high << "]: ";
    for (int p : primes)
        cout << p << " ";
    cout << endl;

    return 0;
}
