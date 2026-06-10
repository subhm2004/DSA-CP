/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : deque_basics.cpp
 * PROBLEM  : Deque Basics
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <deque>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STL DEQUE BASICS — push_front/push_back dono ends se insert
// ────────────────────────────────────────────────────────────────────────────
// front() = pehla element; back() = last element
// double-ended queue — queue + stack dono ki tarah use ho sakta hai
// ════════════════════════════════════════════════════════════════════════════

// ── main: STL deque demo ───────────────────────────────────────────────────
//   1) push_back — rear pe add
//   2) push_front — front pe add
//   3) front/back/size print
int main() {
    deque<int> dq;
    dq.push_back(10);                      // rear enqueue
    dq.push_front(20);                     // front insert — deque advantage
    cout << "Front: " << dq.front() << endl;
    cout << "Rear: " << dq.back() << endl;
    cout << "Size: " << dq.size() << endl;
}
