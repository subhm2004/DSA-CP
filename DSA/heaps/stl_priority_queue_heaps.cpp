/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : stl_priority_queue_heaps.cpp
 * PROBLEM  : Stl Priority Queue Heaps
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STL PRIORITY_QUEUE — Max heap vs Min heap demo
// ────────────────────────────────────────────────────────────────────────────
// priority_queue<int> = max heap (default) — top sabse bada
// priority_queue<int, vector<int>, greater<int>> = min heap — top sabse chhota
// push O(log n), pop O(log n), top O(1)
// k-th smallest: min heap me (k-1) baar pop
// ════════════════════════════════════════════════════════════════════════════

// ── findingksmallest: min heap se k-th chhota nikaalo ──────────────────────
//   1) empty heap -> -1 return
//   2) jab tak k != 1: pop karo, k--
//   3) top() = k-th smallest return
int findingksmallest(priority_queue<int, vector<int>, greater<int>> p, int& k){
    if(p.empty()){
        return -1;
    }
    while(k!= 1){
        p.pop();
        k--;
    }
    return p.top();
}

// ── main: max/min heap operations aur k-smallest demo ────────────────────────
//   1) max heap push/pop/top/size demo
//   2) min heap push demo
//   3) user se k input, findingksmallest call
int main(){
    priority_queue<int>pq; // max heap
    pq.push(10);
    pq.push(20);
    pq.push(30);
    pq.push(40);
    pq.push(50);
    cout<< "topmost element of queue"<< pq.top()<< endl;
    pq.pop();
    cout<< "topmost element of queue: "<< pq.top()<< endl;
    cout<< "size of queue is: "<< pq.size()<< endl;
    if(pq.empty()){
        cout<< "empty"<< endl;
    }
    else {
        cout<< "not empty"<< endl;
    }
    priority_queue<int, vector<int>, greater<int>> p; // min heap
    p.push(10);
    p.push(20);
    p.push(30);
    p.push(40);
    p.push(50);
    p.push(60);
    if(p.empty()){
        cout<< "empty"<< endl;
    }
    else {
        cout<< "not empty"<< endl;
    }
    int k;
    cout<< "enter k"<< endl;
    cin>> k;
    int ans= findingksmallest(p,k);
    cout<< "kth smallest element is: "<< ans << endl;




}
