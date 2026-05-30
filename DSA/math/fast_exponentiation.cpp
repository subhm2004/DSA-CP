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


/*
 * power()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int a, int b
 * Returns : int
 */
int power(int a, int b) {
    int res=1;
    for(int i=1; i<=b; i++) {
        res = res*a;
    }
    return res;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Fast Exponentiation
 */
int main() {
    int a,b;
    cout<< "enter base"<< endl;
    cin>> a;
    cout<< "enter exponent"<< endl;
    cin>> b;
    int ans = power(a,b);
    cout<< "answer is "<< ans<< endl;
}
