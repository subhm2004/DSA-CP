/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : binary_search.cpp
 * PROBLEM  : Binary Search
 * LEETCODE : 704 — Binary Search
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}


/*
 * binary_search()
 * Purpose : Binary search — eliminate half the search space each step.
 * Params  : int arr[], int size, int search
 * Returns : int
 */
int binary_search(int arr[], int size, int search) {
    int i=0, j= size -1;    
    while(i<=j) {
        int mid = (i+j)/2;
        if(arr[mid]== search) {
            return mid+1;
            break;
        }
        else if(arr[mid]< search){
            i= mid +1;
        }
        else if(arr[mid] > search) {
            j= mid-1;
        }
    }
    return -1;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Search
 */
int main() {
    int arr[] = { 1,4,5,7,9,11,23,45};
    int size = 8;
    int search;
    cout<< "enter the elemnet to search"<< endl;
    cin>> search;
    printarray(arr,size);
    int key = binary_search(arr, size, search);
    cout<< key<< endl;

}
