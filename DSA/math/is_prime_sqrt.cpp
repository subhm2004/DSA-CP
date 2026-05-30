/*
 * ============================================================================
 * TOPIC    : Math — Prime Check (Trial Division)
 * FILE     : is_prime_sqrt.cpp
 * PROBLEM  : Check if n is prime
 * LEETCODE : 204 — Count Primes (building block) / general prime test
 * APPROACH : Trial division up to sqrt(n); handle n <= 1 and even n
 * COMPLEX  : Time: O(sqrt n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

vector<int> sievePrimes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= n; j += i)
            isPrime[j] = false;
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

int main() {
    cout << boolalpha;
    cout << isPrime(17) << " " << isPrime(18) << endl; // true false
    auto primes = sievePrimes(30);
    cout << primes.size() << " primes up to 30\n"; // 10
    return 0;
}
