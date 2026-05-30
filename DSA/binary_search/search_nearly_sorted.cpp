/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : search_nearly_sorted.cpp
 * PROBLEM  : Search Nearly Sorted
 * LEETCODE : 540 — Single Element in a Sorted Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * nearlysorted()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int nearlysorted(int *arr, int& size, int& target){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== target){
            return mid;
        }
        else if(mid-1>=0 && arr[mid-1]== target){
            return mid-1;
        }
        else if(mid+1 < size && arr[mid+1]== target){
            return mid+1;
        }
        else if(arr[mid]> target){
            e= mid-2;
        }
        else{
            s= mid+2;
        }
        mid= s+(e-s)/2;    
    }
    return -1;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Search Nearly Sorted
 */
int main(){
    int arr[]={20, 10, 30, 50, 40, 70, 60};
    int size= 7;
    int target= 20;
    int ans= nearlysorted(arr, size, target);
    cout<< ans<< endl;
}
