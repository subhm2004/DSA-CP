/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : interleave_queue.cpp
 * PROBLEM  : Interleave Queue
 * LEETCODE : 950 — Reveal Cards In Order (queue reorder pattern)
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INTERLEAVE QUEUE — first half aur second half alternate merge
// ────────────────────────────────────────────────────────────────────────────
// queue ko do hisson mein todo — q1 (first n/2), q (second half)
// alternate: q1.front, q.front → q2 mein merge
// ════════════════════════════════════════════════════════════════════════════

// ── main: queue interleave demo ─────────────────────────────────────────────
//   1) queue mein elements enqueue (rear push)
//   2) first n/2 elements q1 mein transfer (front pop)
//   3) q1 aur q se alternate merge q2 mein
//   4) q2 print — interleaved order
int main() {
    queue<int> q;
    q.push(10);                            // enqueue rear — FIFO tail
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);
    q.push(80);
    int n = q.size() / 2;
    queue<int> q1;
    while (n--) {
        q1.push(q.front());                // first half — front se dequeue
        q.pop();
    }
    queue<int> q2;
    while (!q.empty() && !q1.empty()) {
        q2.push(q1.front());               // alternate merge — pehle first half
        q2.push(q.front());                // phir second half
        q.pop();
        q1.pop();
    }
    while (!q2.empty()) {
        cout << q2.front() << " ";
        q2.pop();
    }
}
