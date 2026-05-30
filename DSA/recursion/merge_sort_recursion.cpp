/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : merge_sort_recursion.cpp
 * PROBLEM  : Merge Sort Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Divide, sort halves recursively, merge sorted halves.
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * merge()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int* arr, int s, int e
 * Returns : void
 */
void merge(int* arr, int s, int e) {
    int mid = (s+e)/2;
    int length1 = mid-s+1;
    int length2 = e-mid;
    int* left = new int[length1];
    int* right = new int[length2];
    int k=s; 
    for(int i=0; i< length1; i++) {
        left[i] = arr[k]; 
        k++;
    }
    k= mid+1;
    for(int i=0; i< length2; i++) {
        right[i] = arr[k];
        k++;
    }
    int i=0, j=0;
     k = s;
    while(i< length1 && j< length2) {
        if(left[i] < right[j]) {
            arr[k] = left[i];
            i++;
            k++;
        }
        else {
            arr[k] = right[j];
            j++;
            k++;
        }       
    }
    while(i< length1) {
        arr[k++] = left[i++];
    }
    while(j< length2) {
        arr[k++] = right[j++];
    }
}


/*
 * mergesort()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int* arr, int s, int e
 * Returns : void
 */
void mergesort(int* arr, int s, int e) {   
    if(s>=e) {
        return;
    }
    int mid = s+(e-s)/2;
    mergesort(arr, s, mid);
    mergesort(arr, mid+1, e);
    merge(arr, s,e);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Merge Sort Recursion
 */
int main() {
    int arr[] = {12,4,2,1,5};
    int size = 5;
    int s=0, e= size-1;
    mergesort(arr, s,e);
    cout<< "Name: Vanshika Aggarwal"<< endl;
    cout<< "Roll No. 22001003138"<< endl;
    cout<< "sorted array is "<< endl;
    // Iterate over all elements
    for(int i=0; i< size; i++) {
        cout<< arr[i]<< " ";
    }
}
