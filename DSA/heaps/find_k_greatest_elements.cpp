/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : find_k_greatest_elements.cpp
 * PROBLEM  : Find K Greatest Elements
 * LEETCODE : 215 — Kth Largest Element in an Array
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : priority_queue for O(log n) min/max access.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;


/*
 * kgreatest()
 * Purpose : priority_queue for O(log n) min/max access.
 * Params  : int arr[], int& size, int& k
 * Returns : int
 */
int kgreatest(int arr[], int& size, int& k){
    // Min heap — smallest element at top
    priority_queue<int, vector<int>, greater<int>>pq;
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    // Iterate over all elements
    for(int i=k; i<size; i++){
        if(arr[i]> pq.top()){
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}


/*
 * main()
 * Purpose : Entry point — demo/test for Find K Greatest Elements
 */
int main(){
    int arr[]= {3,6,9,8,7,1,2};
    int size= 7;
    int k=3;
    int ans= kgreatest(arr,size,k);
    cout<< ans<< endl;
}
