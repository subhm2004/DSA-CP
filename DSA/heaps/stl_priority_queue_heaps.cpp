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



/*
 * findingksmallest()
 * Purpose : priority_queue for O(log n) min/max access.
 * Params  : priority_queue<int, vector<int>, greater<int>> p, int& k
 * Returns : int
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Stl Priority Queue Heaps
 */
int main(){
    // Min heap — smallest element at top
    priority_queue<int>pq;
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
    priority_queue<int, vector<int>, greater<int>> p;
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
