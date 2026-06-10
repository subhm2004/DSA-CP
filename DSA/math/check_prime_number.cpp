/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : check_prime_number.cpp
 * PROBLEM  : Check Prime Number
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Sieve of Eratosthenes — mark multiples of primes.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRIME CHECK & COUNT — brute force trial division
// ────────────────────────────────────────────────────────────────────────────
// Funda: 2 se n-1 tak divide try — koi divisor mila? not prime
// countprime — har i ke liye check karke total primes count karo
// COMPLEX: O(n^2) brute — learning purpose
// ════════════════════════════════════════════════════════════════════════════

// ── isprime: ek number prime hai ya nahi check ─────────────────────────────
//   1) n<=1? not prime print karo
//   2) i=2 se n-1 — n%i==0? flag=1, break
//   3) flag==0? prime, warna not prime print
void isprime(int n) {
    if(n<=1) {
        cout<< "number is not prime"<< endl;
    }
    int flag=0;
    for(int i=2; i<n; i++) {
        if(n%i==0) {
            flag =1; // divisor mil gaya — composite
            break;
        }
    }
    if(flag==0) {
        cout<< "number is prime"<< endl;
    }
    else {
        cout<< "number is not prime"<< endl;
    }
}

// ── countprime: 2 se n-1 tak kitne primes hain ─────────────────────────────
//   1) har i ke liye inner loop — koi divisor?
//   2) divisor nahi mila? flag++ (i prime hai)
//   3) total count print karo
void countprime(int n) {
    int flag = 0;
    for(int i=2; i< n; i++) {
        int count = 0;
        for(int j=2; j<i; j++) {
            if(i % j == 0) {
                count = 1; // i composite
                break;
            }
        }
        if(count == 0) {
            flag++; // i prime mila
        }
    }
    cout<< "number of prime numbers are "<< flag << endl;
}

// ── main: n input lo, countprime run ─────────────────────────────────────────
//   1) user se n lo, countprime(n) call
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    countprime(n);
}
