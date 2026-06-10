/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : dsa_practice.cpp
 * PROBLEM  : Dsa Practice
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SQUARE ROOT — binary search + decimal precision
// ────────────────────────────────────────────────────────────────────────────
// Funda: integer part BS se — mid*mid vs target
// Decimal part: step=0.1 se refine, har pass step/10 — 2 decimal places
// COMPLEX: Integer BS O(log n)  |  Decimal O(precision steps)
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: 0 se target tak numbers print (helper) ─────────────────────
//   1) 0 se target+1 tak print — visualization ke liye
void printarray( int target, int arr[]) {
   
    cout<< "elements of array are\n";
    for(int i=0; i< target+1; i++) {
        cout<< i << " ";
    }
} 


// ── sqrt: BS se integer square root ────────────────────────────────────────
//   1) i=0, j=target — search space
//   2) mid*mid > target -> j=mid-1
//   3) mid*mid < target -> ans=mid, i=mid+1; equal -> return mid
//   4) ans = floor(sqrt)
int sqrt(  int target) {
    int i=0; 
    int j= target;
    int ans=0;
    while(i<=j) {        
        int mid = i+(j-i)/2;
        if(mid* mid > target) {
            j= mid-1;
        }
        else if(mid * mid < target) {
            ans = mid;
            i= mid+1;
        }
        else {
            return mid;
        }
    
    }
    return ans;
}


// ── main: integer + decimal sqrt demo ──────────────────────────────────────
//   1) target input
//   2) BS se integer root
//   3) step refinement se 2 decimal places tak precise answer
int main() {
    int target;
    cout<< "enter the element to find sqrt"<< endl;
    cin>> target;
    
    int root= sqrt(target);
    cout<< "integer part of square root of target is "<< root<< endl;
    double step = 0.1;
    double final = root;
    for(int i=0; i<2; i++) {
        for(double j= final; j*j < target; j= j+step ) {
             final = j;
        }
        step = step/10;  // har pass 10x precise — 0.1 -> 0.01
    }
    cout<< " final answer is "<< final<< endl;
    return 0;

}
