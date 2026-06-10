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

// ════════════════════════════════════════════════════════════════════════════
// K GREATEST — Min heap of size k (top = k-th largest among window)
// ────────────────────────────────────────────────────────────────────────────
// Pehle k elements min-heap me — top sabse chhota un k me se
// Naya element agar top se bada -> purana min hatao, naya daalo
// End me top = k-th largest element
// O(n log k) space O(k)
// ════════════════════════════════════════════════════════════════════════════

// ── kgreatest: k-th largest using size-k min heap ──────────────────────────
//   1) min_heap (greater<int>) — chhota top pe
//   2) pehle k elements push karo
//   3) baaki: arr[i] > top -> pop smallest of k, push arr[i]
//   4) top = k-th greatest return
int kgreatest(int arr[], int& size, int& k){
    priority_queue<int, vector<int>, greater<int>>pq;
    for(int i=0; i<k; i++){
        pq.push(arr[i]);
    }
    for(int i=k; i<size; i++){
        if(arr[i]> pq.top()){ // naya bada hai current k-th largest se
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

// ── main: fixed k=3 pe demo ────────────────────────────────────────────────
int main(){
    int arr[]= {3,6,9,8,7,1,2};
    int size= 7;
    int k=3;
    int ans= kgreatest(arr,size,k);
    cout<< ans<< endl;
}
