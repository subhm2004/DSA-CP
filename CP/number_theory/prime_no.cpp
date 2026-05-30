#include <bits/stdc++.h>
using namespace std;

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

    // Store prime numbers
    for (int i = 2; i <= N; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }

    return primes;
}

// ✅ Main Function
int main()
{
    int N;
    cout << "Enter N (Find primes up to): ";
    cin >> N;

    vector<int> primes = sieveOfEratosthenes(N);
    cout << "Primes up to " << N << ": ";
    for (int p : primes)
        cout << p << " ";
    cout << endl;

    return 0;
}
