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

// ════════════════════════════════════════════════════════════════════════════
// PRIME CHECK + SIEVE — optimized trial division aur Eratosthenes
// ────────────────────────────────────────────────────────────────────────────
// Funda: isPrime — 6k±1 optimization se sqrt(n) tak check
// sievePrimes — boolean sieve se list banao
// COMPLEX: isPrime O(sqrt n)  |  sieve O(n log log n)
// ════════════════════════════════════════════════════════════════════════════

// ── isPrime: trial division with 6k±1 optimization ─────────────────────────
//   1) n<=1 false; n<=3 true; even/3-divisible false
//   2) i=5 se i*i<=n, i+=6 — n%i aur n%(i+2) check
//   3) koi divisor nahi? true return
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// ── sievePrimes: 2 se n tak primes ki list banao ────────────────────────────
//   1) isPrime bool array — 0,1 false
//   2) i=2 se i*i<=n — multiples mark false from i*i
//   3) true indices ko primes vector me collect, return
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

// ── main: isPrime aur sievePrimes demo ───────────────────────────────────────
//   1) isPrime(17)=true, isPrime(18)=false
//   2) sievePrimes(30) — 10 primes
int main() {
    cout << boolalpha;
    cout << isPrime(17) << " " << isPrime(18) << endl; // true false
    auto primes = sievePrimes(30);
    cout << primes.size() << " primes up to 30\n"; // 10
    return 0;
}
