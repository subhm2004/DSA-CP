/*
 * ============================================================================
 * TOPIC    : Math — Count Primes (Sieve)
 * FILE     : count_primes.cpp
 * PROBLEM  : Count primes strictly less than n
 * LEETCODE : 204 — Count Primes
 * APPROACH : Sieve of Eratosthenes; mark multiples from i*i
 * COMPLEX  : Time: O(n log log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COUNT PRIMES — LeetCode 204 sieve solution
// ────────────────────────────────────────────────────────────────────────────
// Funda: n se chhote saare primes count — boolean sieve use karo
// 0,1 prime nahi; har prime ke multiples false mark
// COMPLEX: Time O(n log log n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
public:
    // ── countPrimes: sieve se n se kam primes count ────────────────────────
    //   1) n<=2? return 0 — koi prime nahi
    //   2) prime[0..n-1] bool array — 0,1 false
    //   3) i=2 se i*i<n — multiples mark false from i*i
    //   4) count true entries — yahi answer
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> prime(n, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i < n; i++) {
            if (!prime[i]) continue; // already composite
            for (int j = i * i; j < n; j += i)
                prime[j] = false; // i ka multiple
        }
        return count(prime.begin(), prime.end(), true);
    }
};

// ── main: LeetCode sample tests ──────────────────────────────────────────────
//   1) countPrimes(10)=4, countPrimes(0)=0 print
int main() {
    cout << Solution().countPrimes(10) << endl; // 4
    cout << Solution().countPrimes(0) << endl;  // 0
    return 0;
}
