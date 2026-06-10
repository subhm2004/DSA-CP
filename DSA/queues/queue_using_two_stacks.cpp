/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : queue_using_two_stacks.cpp
 * PROBLEM  : Queue Using Two Stacks
 * LEETCODE : 232 — Implement Queue using Stacks
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// QUEUE USING TWO STACKS — FIFO ko do LIFO stacks se banao
// ────────────────────────────────────────────────────────────────────────────
// enqueue: st mein push (input stack)
// dequeue: st se sab reverse stack mein transfer, phir pop
// ya amortized: enqueue cheap, dequeue pe lazy transfer
// ════════════════════════════════════════════════════════════════════════════

// ── main: two-stack queue skeleton ───────────────────────────────────────────
//   1) st = input stack (enqueue push)
//   2) reverse = output stack (dequeue pop)
//   3) transfer se FIFO order maintain
int main() {

    stack<int> st;                         // enqueue stack — push yahan
    stack<int> reverse;                    // dequeue stack — pop yahan se
}
