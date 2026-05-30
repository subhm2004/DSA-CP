/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : loops_practice.cpp
 * PROBLEM  : Loops Practice
 * ABOUT    : General practice and mixed problems
 * APPROACH : Floyd's slow/fast pointers detect cycle.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Loops Practice
 */
int main() {
    int n;
    
    cout<< "enter any number "<< endl;
    cin>> n;
    bool isprime=1;
    for(int i=2; i<n; i++) {
        if(n%i==0) {
            isprime=0;
            break;
        }
        
        }
        if(isprime ==0) {
            cout<< "number is not prime"<< endl;
        }
        else {
            cout<< "number is prime"<< endl;
        }
    }
