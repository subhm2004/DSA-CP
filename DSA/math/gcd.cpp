/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : gcd.cpp
 * PROBLEM  : Gcd
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Euclidean algorithm: gcd(a,b) = gcd(b, a%b).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GCD — subtraction based Euclidean variant
// ────────────────────────────────────────────────────────────────────────────
// Funda: bada number se chhota subtract karo jab tak ek zero na ho
// b>a pe b=b-a, warna a=a-b — last non-zero GCD hai
// COMPLEX: O(a+b) worst case — modulo version faster hai
// ════════════════════════════════════════════════════════════════════════════

// ── gcd: subtraction se greatest common divisor ──────────────────────────────
//   1) a==0? return b; b==0? return a — base cases
//   2) while a!=0 — b>a? b-=a, warna a-=b
//   3) return b — yahi GCD
int gcd(int a, int b) {
    if(a==0) {
        return b;
    }
    if(b==0) {
        return a;
    }
    while(a!= 0) {
        if(b>a) {
            b = b-a; // bada se chhota ghatao
        }
        else {
            a = a-b;
        }
    }
    return b;
    
}

// ── main: do numbers input, GCD print ────────────────────────────────────────
//   1) a, b cin se lo
//   2) gcd(a,b) call, answer print
int main() {
    int a, b;
    cout<< "enter two numbers"<< endl;
    cin>> a>> b;
    int ans = gcd(a,b);
    cout<< "gcd is "<< ans << endl;
    return 0;
}
