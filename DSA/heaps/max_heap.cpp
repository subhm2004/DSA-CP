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

// ════════════════════════════════════════════════════════════════════════════
// K SMALLEST VIA MAX HEAP — STL priority_queue demo
// ────────────────────────────────────────────────────────────────────────────
// Size-k max heap: top hamesha k elements me sabse bada (= k-th smallest)
// File name max_heap but logic k-smallest ke liye max heap of size k
// Same pattern as find_k_smallest_elements.cpp
// ════════════════════════════════════════════════════════════════════════════

// ── getksmallest: k-th smallest with max heap of size k ────────────────────
//   1) pehle k elements max-heap me push
//   2) baaki elements: chhota mila to pop+push
//   3) heap size k maintain — top = k-th smallest
//   4) top return
int getksmallest(int arr[], int &size, int &k){
    priority_queue<int>pq; // default = max heap
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    for(int i=k; i< size; i++){
        if(arr[i]< pq.top()){
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

// ── main: k=3 pe test ───────────────────────────────────────────────────────
int main(){
    int arr[]= {3,4,7,9,8,1,6};
    int size= 7;
    int k=3;
    int ans= getksmallest(arr,size,k);
    cout<< ans<< endl;   
}
