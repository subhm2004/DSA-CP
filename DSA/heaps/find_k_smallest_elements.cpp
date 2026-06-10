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

// ════════════════════════════════════════════════════════════════════════════
// K SMALLEST — Max heap of size k (top = k-th smallest among window)
// ────────────────────────────────────────────────────────────────────────────
// Pehle k elements max-heap me daalo
// Baaki elements: agar arr[i] < top -> pop + push (heap size k rakho)
// End me top = k-th smallest overall
// O(n log k) — har element pe ek heap op
// ════════════════════════════════════════════════════════════════════════════

// ── ksmallest: k-th smallest using size-k max heap ─────────────────────────
//   1) pehle k elements max-heap me push (default pq = max heap)
//   2) i=k se end: agar arr[i] < pq.top() -> purana max hatao, naya daalo
//   3) heap hamesha k elements rakhta hai — top sabse bada unme se
//   4) top() = k-th smallest return
int ksmallest(int arr[], priority_queue<int>pq, int& size, int& k){
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    for(int i=k; i<size; i++){
        if(arr[i]< pq.top()){ // naya element chhota hai current k-th se
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

// ── main: user se k input, result print ──────────────────────────────────────
int main(){
    int arr[]= {3,7,4,5,6,8,9};
    int size= 7;
    priority_queue<int>pq; // max heap — top = current k-th smallest
    int k;
    cout<< "Enter k"<< endl;
    cin>> k;
    cout<< "kth smallest element is: "<< ksmallest(arr,pq,size,k)<< endl;
}
