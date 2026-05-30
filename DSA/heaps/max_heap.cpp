/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : max_heap.cpp
 * PROBLEM  : Max Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;


/*
 * getksmallest()
 * Purpose : priority_queue for O(log n) min/max access.
 * Params  : int arr[], int &size, int &k
 * Returns : int
 */
int getksmallest(int arr[], int &size, int &k){
    // Min heap — smallest element at top
    priority_queue<int>pq;
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    // Iterate over all elements
    for(int i=k; i< size; i++){
        if(arr[i]< pq.top()){
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}


/*
 * main()
 * Purpose : Entry point — demo/test for Max Heap
 */
int main(){
    int arr[]= {3,4,7,9,8,1,6};
    int size= 7;
    int k=3;
    int ans= getksmallest(arr,size,k);
    cout<< ans<< endl;   
}
