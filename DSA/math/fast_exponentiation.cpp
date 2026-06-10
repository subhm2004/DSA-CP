/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : fast_exponentiation.cpp
 * PROBLEM  : Fast Exponentiation
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// POWER — naive exponentiation (learning version)
// ────────────────────────────────────────────────────────────────────────────
// Funda: res=1 se start, b baar multiply — a^b
// Fast version binary exponentiation se O(log b) hota hai
// Yahan simple loop O(b) — basics ke liye
// ════════════════════════════════════════════════════════════════════════════

// ── power: a ko b times multiply karke a^b nikalo ───────────────────────────
//   1) res=1 initialize
//   2) i=1 se b tak res = res * a
//   3) final res return
int power(int a, int b) {
    int res=1;
    for(int i=1; i<=b; i++) {
        res = res*a; // ek aur factor multiply
    }
    return res;
}

// ── main: base aur exponent input, result print ────────────────────────────
//   1) a, b user se lo
//   2) power(a,b) call, answer print
int main() {
    int a,b;
    cout<< "enter base"<< endl;
    cin>> a;
    cout<< "enter exponent"<< endl;
    cin>> b;
    int ans = power(a,b);
    cout<< "answer is "<< ans<< endl;
}
