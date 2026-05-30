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
 
 
 /*
  * isprime()
  * Purpose : Sieve of Eratosthenes — mark multiples of primes.
  * Params  : int n
  * Returns : void
  */
 void isprime(int n) {
    if(n<=1) {
        cout<< "number is not prime"<< endl;
    }
    int flag=0;
    for(int i=2; i<n; i++) {
        if(n%i==0) {
            flag =1;
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



/*
 * countprime()
 * Purpose : Sieve of Eratosthenes — mark multiples of primes.
 * Params  : int n
 * Returns : void
 */
void countprime(int n) {
    int flag = 0;
    for(int i=2; i< n; i++) {
        int count = 0;
        for(int j=2; j<i; j++) {
            if(i % j == 0) {
                count = 1;
                break;
            }
        }
        if(count == 0) {
            flag++;
        }
    }
    cout<< "number of prime numbers are "<< flag << endl;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Check Prime Number
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    countprime(n);
}
