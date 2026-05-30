/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : bubble_sort_recursion.cpp
 * PROBLEM  : Bubble Sort Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Swap adjacent out-of-order elements until sorted.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * bubblesort()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size
 * Returns : void
 */
void bubblesort(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<size-1; i++) {
        // Iterate over all elements
        for(int j=0; j<size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


/*
 * bubblesort2()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int *arr, int& size, int i, int j
 * Returns : void
 */
void bubblesort2(int *arr, int& size, int i, int j) {
    if(i>= size-1 || j>= size-i-1) {
        return;
    }
    
    if(arr[j] > arr[j+1]) {
        swap(arr[j], arr[j+1]);
    }
    bubblesort2(arr,size,i,j+1);
    bubblesort2(arr, size, i+1,j );
}



/*
 * printarray()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int *arr, int size
 * Returns : void
 */
void printarray(int *arr, int size) {
    cout<< "sorted array is "<< endl;
    // Iterate over all elements
    for(int i=0; i < size; i++) {
        cout<< arr[i]<< " ";
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Bubble Sort Recursion
 */
int main() {
    int arr[] = { 12,1,8,90,4,2};
    int size = 6;
    int i=0, j= 0;
    bubblesort2(arr, size, i, j);
    printarray(arr, size);   
}
