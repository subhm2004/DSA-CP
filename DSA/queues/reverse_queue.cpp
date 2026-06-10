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

// ════════════════════════════════════════════════════════════════════════════
// REVERSE QUEUE — iterative (stack) ya recursive approach
// ────────────────────────────────────────────────────────────────────────────
// iterative: sab dequeue → stack push → stack pop → enqueue
// recursive: front nikaalo, baaki reverse, phir rear push
// ════════════════════════════════════════════════════════════════════════════

// ── reversequeue: stack se queue reverse ─────────────────────────────────────
//   1) sab elements front se pop → stack push
//   2) stack se pop → queue rear push
//   3) LIFO se FIFO reverse ho jata hai
void reversequeue(queue<int> &q) {
    stack<int> st;
    while (!q.empty()) {
        st.push(q.front());                // dequeue front
        q.pop();
    }
    while (!st.empty()) {
        q.push(st.top());                  // enqueue rear — reversed
        st.pop();
    }
}

// ── recursionreverse: recursive queue reverse ───────────────────────────────
//   1) base: empty queue
//   2) front pop, baaki reverse recurse
//   3) temp rear push — last mein pehla element
void recursionreverse(queue<int> &q) {
    if (q.empty()) {
        return;
    }
    int temp = q.front();
    q.pop();                               // front dequeue
    recursionreverse(q);
    q.push(temp);                          // rear enqueue — reverse build
}

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    recursionreverse(q);
}
