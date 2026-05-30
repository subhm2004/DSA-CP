/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : binary_quotient.cpp
 * PROBLEM  : Binary Quotient
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



/*
 * quotient()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int dividend, int divisor
 * Returns : int
 */
int quotient(int dividend, int divisor) {
    int i = 0;
    int j = dividend;
    int mid = i+(j-i)/2;
    int ans=0;
    while(i<=j) {
        if(mid*divisor > dividend) {
            j= mid-1;
        }
        else if(mid*divisor <= dividend) {
            ans= mid;
            i= mid +1;
        }
        
        mid = i+ (j-i)/2;
       
}
return ans;
 
}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Quotient
 */
int main() {
    int dividend, divisor;
    cout<< "enter dividend and divisor"<< endl;
    cin >> dividend >> divisor;
    int final= quotient(dividend, divisor);
    cout<< "\n required quotient is "<< final<< endl;
    return 0;

}
