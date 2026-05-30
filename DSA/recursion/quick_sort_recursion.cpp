/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : quick_sort_recursion.cpp
 * PROBLEM  : Quick Sort Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Partition around pivot; recursively sort left and right.
 * COMPLEX  : Time: O(n log n) avg  |  Space: O(log n)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * partition()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int* arr, int s, int e
 * Returns : int
 */
int partition(int* arr, int s, int e ) {
    int pivotindex = s;
    int pivotelement = arr[s];
    int count =0;
    for(int i=s+1; i<=e; i++) {
        if(arr[i] <= pivotelement) {
            count++;
        }
    }
    int rightindex = s + count;
    swap(arr[pivotindex], arr[rightindex]);
    pivotindex = rightindex;
    int i=s, j= e;
    while(i< pivotindex && j> pivotindex) {
        while(arr[i] < pivotelement) {
            i++;
        }
        while(arr[j] > pivotelement) {
            j--;
        }
        if(i< pivotindex && j> pivotindex) {
            swap(arr[i], arr[j]);
        }
    }
    return pivotindex;
}


/*
 * quicksort()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int* arr, int s, int e
 * Returns : void
 */
void quicksort(int* arr, int s, int e) {
    if(s>=e) {
        return;
    }
    int p= partition(arr, s, e);
    quicksort(arr, s, p-1);
    quicksort(arr, p+1, e);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Quick Sort Recursion
 */
int main() {
    int arr[] = {8,1,3,4,20,50,30};
    int size = 7;
    int s=0, e = size-1;
    quicksort(arr, s, e);
    cout<< "sorted array is "<< endl;
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i] << " ";
    } cout<< endl;
}
