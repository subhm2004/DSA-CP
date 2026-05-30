/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : aggressive_cows.cpp
 * PROBLEM  : Aggressive Cows
 * LEETCODE : 410 — Split Array Largest Sum (BS on answer — GFG variant)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;


/*
 * ispossible()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& mid, int& k
 * Returns : bool
 */
bool ispossible(int *arr, int& size, int& mid, int& k){
    int cowcount= 1;
    int stallallocate= arr[0];
    // Iterate over all elements
    for(int i=1; i<size; i++){
        if(arr[i]-stallallocate>= mid){
            cowcount++;
            stallallocate= arr[i];
        }
        if(cowcount==k){
            return true;
        }
    }
    return false;
}


/*
 * mindistance()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& k
 * Returns : int
 */
int mindistance(int *arr, int& size, int& k){
    sort(arr,arr+size);
    int s=0;
    int e= arr[size-1];
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(ispossible(arr,size,mid,k)){
            ans= mid;
            s= mid+1;
        }
        else {
            e= mid-1;
        }
        mid= s+(e-s)/2;
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Aggressive Cows
 */
int main(){
    int arr[]= {10,1,2,7,5};
    int size= 5;
    int k= 3;
    int ans= mindistance(arr,size,k);
    cout<< ans<< endl;
}
