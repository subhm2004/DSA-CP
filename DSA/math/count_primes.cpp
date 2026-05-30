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

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> prime(n, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i < n; i++) {
            if (!prime[i]) continue;
            for (int j = i * i; j < n; j += i)
                prime[j] = false;
        }
        return count(prime.begin(), prime.end(), true);
    }
};

int main() {
    cout << Solution().countPrimes(10) << endl; // 4
    cout << Solution().countPrimes(0) << endl;  // 0
    return 0;
}
