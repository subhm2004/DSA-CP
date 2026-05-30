/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : unbounded_binary_search.cpp
 * PROBLEM  : Unbounded Binary Search
 * LEETCODE : 704 — Binary Search (unbounded range)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * binarysearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int i, int j, int & target
 * Returns : int
 */
int binarysearch(int *arr, int i, int j, int & target){
    int mid= i+j/2;
    while(i<=j){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid]> target){
            j= mid-1;
        }
        else {
            i= mid+1;
        }
        mid= i+j/2;
    }
    return -1;

}


/*
 * unboundedsearch()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& target
 * Returns : int
 */
int unboundedsearch(int *arr, int& target){
    int i=0, j= i+1;
    while(arr[j]<target){
        i=j;
        j<<1;
    }
    return binarysearch(arr,i,j,target);

}


/*
 * main()
 * Purpose : Entry point — demo/test for Unbounded Binary Search
 */
int main() {

    
}
