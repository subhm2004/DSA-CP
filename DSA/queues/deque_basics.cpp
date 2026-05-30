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


/*
 * main()
 * Purpose : Entry point — demo/test for Deque Basics
 */
int main(){
    deque<int>dq;
    dq.push_back(10);
    dq.push_front(20);
    cout<< "Front: "<< dq.front()<< endl;
    cout<< "Rear: "<< dq.back()<< endl;
    cout<< "Size: "<< dq.size()<< endl;
}
