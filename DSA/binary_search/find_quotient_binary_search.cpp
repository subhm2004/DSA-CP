/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : find_quotient_binary_search.cpp
 * PROBLEM  : Find Quotient Binary Search
 * LEETCODE : 29 — Divide Two Integers
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// QUOTIENT VIA BS — Divide without / operator (Leetcode 29)
// ────────────────────────────────────────────────────────────────────────────
// mid*divisor compare dividend se
// mid*divisor <= dividend -> ans=mid, s=mid+1
// Floor quotient return
// ════════════════════════════════════════════════════════════════════════════


// ── quotient: quotient BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int quotient(int& dividend, int& divisor){
    int s=0, e= dividend;
    int mid= s+(e-s)/2;
    int ans=-1;
    while(s<=e){
        if(mid*divisor== dividend){
            return mid;
        }
        else if(mid* divisor > dividend){
            e= mid-1;
        }
        else {
            ans= mid;
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return ans;
}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){
    int dividend, divisor;
    cout<< "enter dividend"<< endl;
    cin>> dividend;
    cout<< "enter divisor"<< endl;
    cin>> divisor;
    int ans= quotient(dividend, divisor);
    cout<< ans<< endl;
}
