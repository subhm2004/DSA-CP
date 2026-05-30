/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : merge_sort.cpp
 * PROBLEM  : Merge Sort
 * LEETCODE : 912 — Sort an Array
 * ABOUT    : Comparison-based sorting algorithms
 * APPROACH : Divide, sort halves recursively, merge sorted halves.
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * mergearray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int *arr, int s, int e
 * Returns : void
 */
void mergearray(int *arr, int s, int e){
    int mid= s+(e-s)/2;
    int size1= mid-s+1;
    int *left = new int[size1];
    int size2= e-mid;
    int *right= new int[size2];
    int k= s;
    // Iterate over all elements
    for(int i=0;i< size1; i++){
        left[i]= arr[k];
        k++;
    }
    k= mid+1;
    // Iterate over all elements
    for(int i=0;i< size2; i++){
        right[i]= arr[k];
        k++;
    }

    int i=0, j=0;
    int index=s;
    while(i<size1 && j<size2){
        if(left[i]<= right[j]){
            arr[index]= left[i];
            index++;
            i++;
        }
        else if(right[j]< left[i]){
            arr[index]= right[j];
            index++;
            j++;
        }
    }
    while(i<size1){
        arr[index++]= left[i++];
    }
    while(j<size2){
        arr[index++]= right[j++];
    }
}


/*
 * mergesort()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int *arr, int s, int e
 * Returns : void
 */
void mergesort(int *arr, int s, int e){
    if(s>=e){
        return;
    }
    int mid= s+(e-s)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    mergearray(arr,s,e);

}


/*
 * main()
 * Purpose : Entry point — demo/test for Merge Sort
 */
int main(){
    int arr[]= {23,2,11,4,1,33,10};
    int size= 7;
    int s=0, e= size-1;
    mergesort(arr,s,e);
    // Iterate over all elements
    for(int i=0; i<size; i++){
        cout<< arr[i]<< " ";
    }

}
