/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : circular_queue_implementation.cpp
 * PROBLEM  : Circular Queue Implementation
 * LEETCODE : 622 — Design Circular Queue
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CIRCULAR QUEUE — array wrap-around se space reuse
// ────────────────────────────────────────────────────────────────────────────
// full: (rear==size-1 && front==0) || (rear==front-1)
// rear end pe → rear=0 wrap; front end pe → front=0 wrap
// empty: front==-1 && rear==-1
// ════════════════════════════════════════════════════════════════════════════

class CQueue {
public:
    int front;
    int rear;
    int *arr;
    int size;
    CQueue(int s) {
        this->size = s;
        this->front = -1;
        this->rear = -1;
        arr = new int[size];
    }

    // ── isfull: circular queue bhar gaya? ────────────────────────────────────
    //   1) rear last + front first, ya rear ek step peeche front
    bool isfull() {
        if ((rear == size - 1 && front == 0) || (rear == front - 1)) {
            return true;
        } else {
            return false;
        }
    }

    // ── isempty: queue khali? ────────────────────────────────────────────────
    bool isempty() {
        if (front == -1 && rear == -1) {
            return true;
        } else {
            return false;
        }
    }

    // ── push: rear se circular enqueue ───────────────────────────────────────
    void push(int data) {
        if (isfull()) {
            cout << "queue overflow" << endl;
        } else if (rear == size - 1 && front != 0) {
            rear = 0;                        // wrap — end se start pe jao
            arr[rear] = data;
        } else {
            if (front == -1 && rear == -1) {
                front = 0;                   // pehla element
            }
            rear++;
            arr[rear] = data;                // normal rear enqueue
        }
    }

    // ── pop: front se circular dequeue ───────────────────────────────────────
    void pop() {
        if (isempty()) {
            cout << "stack underflow" << endl;
        } else if (front == rear) {
            arr[front] = -1;
            front = -1;
            rear = -1;                     // last element — reset
        }
        if (front == size - 1) {
            front = 0;                     // circular wrap — front start pe
        } else {
            arr[front] = 0;
            front++;                       // normal front dequeue
        }
    }

    // ── print: front/rear pointers aur array state ───────────────────────────
    void print() {
        cout << "front: " << front << endl;
        cout << "rear: " << rear << endl;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    CQueue *cq = new CQueue(5);
    cq->push(10);
    cq->print();

    cq->push(20);
    cq->print();

    cq->push(30);
    cq->print();

    cq->push(40);
    cq->print();
    cq->push(50);
    cq->print();

    cq->pop();
    cq->print();

    cq->push(50);
    cq->print();
}
