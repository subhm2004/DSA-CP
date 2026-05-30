/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : reverse_k_queue_elements.cpp
 * PROBLEM  : Reverse K Queue Elements
 * LEETCODE : 25 — Reverse Nodes in k-Group
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;


/*
 * reversekgrp()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : queue<int>&q, int& n, int &k
 * Returns : void
 */
void reversekgrp(queue<int>&q,int& n, int &k){
    stack<int>st;
    int rem= n-k;
    while(k--){
        st.push(q.front());
        q.pop();     
    }
    while(!st.empty()){
        q.push(st.top());
        st.pop();
    }
    while(rem--){
        int temp = q.front();
        q.pop();
        q.push(temp);
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Reverse K Queue Elements
 */
int main(){
    queue<int>q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    int n= q.size();
    int k;
    cout<< "enter k"<< endl;
    cin>> k;
    reversekgrp(q,n,k);
    while(!q.empty()){
        cout<< q.front()<< " ";
        q.pop();
    }
}
