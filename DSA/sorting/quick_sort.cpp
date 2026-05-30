/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : quick_sort.cpp
 * PROBLEM  : Quick Sort
 * LEETCODE : 912 — Sort an Array
 * ABOUT    : Comparison-based sorting algorithms
 * APPROACH : Partition around pivot; recursively sort left and right.
 * COMPLEX  : Time: O(n log n) avg  |  Space: O(log n)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * partition()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int *arr, int s, int e
 * Returns : int
 */
int partition(int *arr, int s, int e){
    int pivotindex= s;
    int pivotelement= arr[s];
    int count=0;
    for(int i=s+1; i<=e; i++){
        if(arr[i]<=pivotelement){
            count++;
        }
    }
    int rightindex= s+count;
    swap(arr[pivotindex], arr[rightindex]);
    pivotindex= rightindex;
    int i=s;
    int j=e;
    while(i<pivotindex && j>pivotindex ){
        if(arr[i]< pivotelement){
            i++;
        }
        if(arr[j]> pivotelement){
            j--;
        }
    }
        if(i<pivotindex && j> pivotindex){
            swap(arr[i], arr[j]);
        }
    
    return pivotindex;
}


/*
 * quicksort()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int* arr, int s, int e
 * Returns : void
 */
void quicksort(int* arr, int s, int e){
    if(s>=e){
        return ;
    }
    int index= partition(arr,s,e);
    quicksort(arr,s,index-1);
    quicksort(arr,index+1,e);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Quick Sort
 */
int main(){
    int arr[]= {12,11,1,56,34,23,22};
    int size= 7;
    int s=0, e= size-1;
    quicksort(arr,s,e);
    // Iterate over all elements
    for(int i=0; i< size; i++){
        cout<< arr[i]<< " ";
    }
}
