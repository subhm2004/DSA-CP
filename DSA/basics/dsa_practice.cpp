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


/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int target, int arr[]
 * Returns : void
 */
void printarray( int target, int arr[]) {
   
    cout<< "elements of array are\n";
    for(int i=0; i< target+1; i++) {
        cout<< i << " ";
    }
} 


/*
 * sqrt()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int target
 * Returns : int
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Dsa Practice
 */
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
        step = step/10;
    }
    cout<< " final answer is "<< final<< endl;
    return 0;

}
