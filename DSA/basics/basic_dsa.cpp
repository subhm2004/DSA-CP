/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : basic_dsa.cpp
 * PROBLEM  : Basic Dsa
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * nearlysorted()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int>arr, int target
 * Returns : int
 */
int nearlysorted(vector<int>arr,  int target) {
    int i=0;
    int j= arr.size() -1;
    int mid= i+(j-i)/2;
    while(i<=j) {
        if(arr[mid]== target) {
            return mid;
        }
        else if(arr[mid+1]== target) {
            return mid+1;
        }
        else if(arr[mid-1]== target) {
            return mid-1;
        }
        else if(arr[mid]> target) {
            j= mid-2;
        }
        else {
            i= mid+2;
        }
        mid = i+(j-i)/2;
    }
    return -1;
   }
   
   
   /*
    * main()
    * Purpose : Entry point — demo/test for Basic Dsa
    */
   int main() {
    vector<int> arr = {10,3,40,20,50,80,70};
    int target = 70;
    int ans= nearlysorted(arr,target);
    cout<< "index of target element is "<< ans<< endl;
    return 0;
   }
