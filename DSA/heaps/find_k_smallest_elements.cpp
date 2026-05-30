/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : find_k_smallest_elements.cpp
 * PROBLEM  : Find K Smallest Elements
 * LEETCODE : 215 — Kth Largest Element in an Array
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Min heap or quickselect for k-th statistic.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;



/*
 * ksmallest()
 * Purpose : priority_queue for O(log n) min/max access.
 // Min heap — smallest element at top
 * Params  : int arr[], priority_queue<int>pq, int& size, int& k
 * Returns : int
 */
// Min heap — smallest element at top
int ksmallest(int arr[], priority_queue<int>pq, int& size, int& k){
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    // Iterate over all elements
    for(int i=k; i<size; i++){
        if(arr[i]< pq.top()){
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}


/*
 * main()
 * Purpose : Entry point — demo/test for Find K Smallest Elements
 */
int main(){
    int arr[]= {3,7,4,5,6,8,9};
    int size= 7;
    // Min heap — smallest element at top
    priority_queue<int>pq;
    int k;
    cout<< "Enter k"<< endl;
    cin>> k;
    cout<< "kth smallest element is: "<< ksmallest(arr,pq,size,k)<< endl;
}
