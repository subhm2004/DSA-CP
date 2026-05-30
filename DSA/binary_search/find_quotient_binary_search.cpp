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


/*
 * quotient()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int& dividend, int& divisor
 * Returns : int
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Find Quotient Binary Search
 */
int main(){
    int dividend, divisor;
    cout<< "enter dividend"<< endl;
    cin>> dividend;
    cout<< "enter divisor"<< endl;
    cin>> divisor;
    int ans= quotient(dividend, divisor);
    cout<< ans<< endl;
}
