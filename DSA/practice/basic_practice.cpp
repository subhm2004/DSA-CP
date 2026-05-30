/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : basic_practice.cpp
 * PROBLEM  : Basic Practice
 * ABOUT    : General practice and mixed problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;


/*
 * slowexponentiation()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int &a, int b
 * Returns : int
 */
int slowexponentiation(int &a, int b ){
    if(b==1){
        return a;
    }
    return a*slowexponentiation(a,b-1);
}


/*
 * fastexponentiation()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int &a, int& b
 * Returns : int
 */
int fastexponentiation(int &a, int& b){
    if(b==0){
        return 1;
    }
    int ans= 1;
    while(b>0){
        if(b&1){
            ans= ans*a;
        }
        a= a*a;
        b= b>>1;
    }
    return ans;
}


/*
 * sieveeratosthenus()
 * Purpose : Sieve of Eratosthenes — mark multiples of primes.
 * Params  : int &n
 * Returns : int
 */
int sieveeratosthenus(int &n){
    // Base case: n == 0
    if(n==0){
        return 0;
    }
    vector<bool>prime(n+1,true); // sbko prime mark krdia initially
    prime[0]= prime[1]= false; 
    int ans=0;// ye prime nhi h
    int N= sqrt(n);
    for(int i=2; i<=N; i++){ // optimisation2
        if(prime[i]){
            ans++;
            int j= i*i;

            while(j<=n){
                prime[j]= false;
                j= j+i;
            }

        }
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Basic Practice
 */
int main(){
    int n;
    cout<< "enter any number"<< endl;
    cin>>n;
    int ans= sieveeratosthenus(n);
    cout<< ans<< endl;  
}
