/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : exponential_search.cpp
 * PROBLEM  : Exponential Search
 * LEETCODE : 704 — Binary Search (exponential search variant)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;


/*
 * binarysearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int s, int e, int& target
 * Returns : int
 */
int binarysearch(int *arr, int& size, int s, int e, int& target){
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid]> target){
            e= mid-1;
        }
        else{
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return -1;
}


/*
 * exponential()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int exponential(int *arr, int& size, int& target){
    if(arr[0]== target){
        return 0;
    }
    int i=1;
    while(i<size && arr[i]<= target){
        i= i<<1;
    }
    return binarysearch(arr, size, i/2, min(i,size-1),target);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Exponential Search
 */
int main(){
    int arr[] = {3,4,5,6,11,13,14,15,56,70};
    int size= 10;
    int target= 70;
    int ans= exponential(arr,size,target);
    cout<< ans<< endl;


}
