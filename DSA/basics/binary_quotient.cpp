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

// ════════════════════════════════════════════════════════════════════════════
// BINARY SEARCH QUOTIENT — division without / operator
// ────────────────────────────────────────────────────────────────────────────
// Funda: quotient = max mid jahan mid*divisor <= dividend
// BS on answer — mid*divisor > dividend -> j=mid-1, warna ans=mid, i=mid+1
// COMPLEX: Time O(log dividend)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── quotient: BS se integer quotient nikalo ────────────────────────────────
//   1) i=0, j=dividend — search space for quotient
//   2) mid*divisor > dividend -> quotient kam karo (j=mid-1)
//   3) mid*divisor <= dividend -> ans=mid, aur bada try (i=mid+1)
//   4) final ans return — integer division result
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


// ── main: dividend/divisor input, quotient print ───────────────────────────
//   1) cin se dividend, divisor
//   2) quotient() call — result print
int main() {
    int dividend, divisor;
    cout<< "enter dividend and divisor"<< endl;
    cin >> dividend >> divisor;
    int final= quotient(dividend, divisor);
    cout<< "\n required quotient is "<< final<< endl;
    return 0;

}
