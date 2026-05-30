/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : reverse_queue.cpp
 * PROBLEM  : Reverse Queue
 * LEETCODE : 206 — Reverse Linked List (queue reverse pattern)
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


/*
 * reversequeue()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : queue<int>&q
 * Returns : void
 */
void reversequeue(queue<int>&q){
    stack<int>st;
    while(!q.empty()){
        st.push(q.front());
        q.pop();
    }
    while(!st.empty()){
        q.push(st.top());
        st.pop();
    }
}


/*
 * recursionreverse()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : queue<int>&q
 * Returns : void
 */
void recursionreverse(queue<int>&q){
    if(q.empty()){
        return;
    }
    int temp= q.front();
    q.pop();
    recursionreverse(q);
    q.push(temp);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Reverse Queue
 */
int main(){
    queue<int>q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    recursionreverse(q);
}
