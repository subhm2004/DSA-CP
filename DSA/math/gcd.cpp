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


/*
 * gcd()
 * Purpose : Euclidean algorithm: gcd(a,b) = gcd(b, a%b).
 * Params  : int a, int b
 * Returns : int
 */
int gcd(int a, int b) {
    if(a==0) {
        return b;
    }
    if(b==0) {
        return a;
    }
    while(a!= 0) {
        if(b>a) {
            b = b-a;
        }
        else {
            a = a-b;
        }
    }
    return b;
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Gcd
 */
int main() {
    int a, b;
    cout<< "enter two numbers"<< endl;
    cin>> a>> b;
    int ans = gcd(a,b);
    cout<< "gcd is "<< ans << endl;
    return 0;
}
