/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : total_occurrences.cpp
 * PROBLEM  : Total Occurrences
 * LEETCODE : 34 — Find First and Last Position of Element in Sorted Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * firstocc()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int firstocc(int *arr, int& size, int& target) {
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e) {
        if(arr[mid] == target) {
            ans = mid;
            e= mid-1;
        }
        else if(arr[mid] > target) {
            e= mid-1;
        }
        else {
            s= mid+1;
        }
    }
    return ans;
}


/*
 * lastocc()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int lastocc(int *arr, int& size, int& target) {
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    int ans1 = -1;
    while(s<=e) {
        if(arr[mid] == target) {
            ans1 = mid;
            s= mid+1;
        }
        else if(arr[mid] < target) {
            s= mid+1;
        }
        else {
            e= mid-1;
        }
    }
    return ans1;
}


/*
 * totalocc()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size, int& target
 * Returns : int
 */
int totalocc(int *arr, int& size, int& target) {
    int c= lastocc(arr, size, target);
    int d= firstocc(arr, size, target);
    int total = c -d + 1;
    return total;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Total Occurrences
 */
int main() {
    int arr[] = {10,20,30,30,30,30,30,40,50,60};
    int size= 10;
    int target = 30;
    int a= totalocc(arr, size, target);
    cout<< a<< endl;    
}
