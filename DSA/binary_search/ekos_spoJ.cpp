/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : ekos_spoj.cpp
 * PROBLEM  : Ekos Spoj
 * LEETCODE : 410 — Split Array Largest Sum (binary search on answer)
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
 * Params  : int *arr, int& size, int& woodreq, int& mid
 * Returns : bool
 */
bool ispossible(int *arr, int& size, int& woodreq, int& mid){
    int sum = 0;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        if(arr[i]- mid> 0){
            sum = sum+ (arr[i]- mid);
        }
    }
    if(sum>= woodreq){
        return true;
    }
    else {
        return false;
    }
}


/*
 * maximumheight()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& woodreq
 * Returns : int
 */
int maximumheight(int *arr, int& size, int& woodreq){
    int maxi= -1;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        maxi= max(maxi, arr[i]);
    }
    int ans= -1;
    int s=0;
    int e= *max_element(arr, arr+size); // stl function
    int mid= s+(e-s)/2;
    while(s<=e){
        if(ispossible(arr, size,woodreq,mid)){
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
 * Purpose : Entry point — demo/test for Ekos Spoj
 */
int main(){
    int arr[]= {4,42,40,26,46};
    int size= 5;
    int woodreq= 20;
    int f= maximumheight(arr,size,woodreq);
    cout<< f<< endl;
}
