/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : two_sum.cpp
 * PROBLEM  : Two Sum
 * LEETCODE : 1 — Two Sum
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Hash map or two pointers to find pair with target sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * twosum()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int& size, int& sum
 * Returns : bool
 */
bool twosum(int arr[], int& size, int& sum) {
    // Iterate over all elements
    for(int i=0; i< size-1; i++) {
        // Iterate over all elements
        for(int j=i+1; j< size; j++) {
            if(arr[i] + arr[j]== sum) {
                return true;
            }
        }
    }
    return false;
}


/*
 * bubblesort()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void bubblesort(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {  // loop for number of rounds
        // Iterate over all elements
        for(int j=0; j< size-i-1; j++) {
            if(arr[j]> arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i< size; i++) {
        cout<< arr[i] << " ";
    }
}


/*
 * merge()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int& s, int& e
 * Returns : void
 */
void merge(int arr[], int& s, int& e) {
    int mid = s+(e-s)/2;
    int length1 = mid -s+1;
    int length2= e- mid;
    int* left= new int[length1];
    int* right = new int[length2];
    int k=s;
    for(int i=0; i<length1; i++) {
        left[i] = arr[k];
        k++;
    }
    k = mid+1;
    for(int i= 0; i< length2; i++) {
        right[i] = arr[k];
        k++;
    }
    int i=0, j=0;
    int mainindex = s;
    while(i< length1 && j< length2) {
        if(left[i]< right[j]) {
            arr[mainindex++] = left[i++] ;
        }
        else {
            arr[mainindex++] = right[j++];
        }   
    }
    while(i< length1) {
        arr[mainindex++] = left[i++];
    }
    while(j< length2){
        arr[mainindex++] = right[j++];
    }
}


/*
 * mergesort()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int s, int& e
 * Returns : void
 */
void mergesort(int arr[], int s, int& e) {
    if(s>=e) {
        return;
    }
    int mid = s+(e-s)/2;
    mergesort(arr, s, mid);
    mergesort(arr, mid+1, e);
    merge(arr, s, e);
}


/*
 * twosum2()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int& size, int& s, int& e, int& sum
 * Returns : void
 */
void twosum2(int arr[], int& size,int& s, int& e, int& sum) {
    mergesort(arr, s, e);
    printarray(arr, size);
    cout<< endl;
    int i=0, j= size-1;
    while(i<j) {
        if(arr[i] + arr[j] == sum) {
            cout<< arr[i]<< " "<< arr[j]<< endl;
            break;
        }
        else if(arr[i] + arr[j] > sum) {
            j--;
        }
        else {
            i++;
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Two Sum
 */
int main() {
    int arr[] = {1,45,4,6,10,8};
    int size = 6;
    int s=0, e= size-1;
    int sum = 16;
    twosum2(arr, size, s, e, sum);
    
}
