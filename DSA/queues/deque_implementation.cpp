/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : deque_implementation.cpp
 * PROBLEM  : Deque Implementation
 * LEETCODE : 239 — Sliding Window Maximum (deque pattern)
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DEQUE IMPLEMENTATION — circular array, front aur rear dono ends
// ────────────────────────────────────────────────────────────────────────────
// pushrear/popfront = normal queue; pushfront/poprear = deque extras
// circular wrap + full/empty checks — same as circular queue logic
// ════════════════════════════════════════════════════════════════════════════

class DEqueue {
public:
    int *arr;
    int front;
    int rear;
    int size;

    DEqueue(int s) {
        this->size = s;
        front = -1;
        rear = -1;
        arr = new int[size];
    }

    // ── isfull: circular deque bhar gaya? ────────────────────────────────────
    //   1) rear at end + front at 0, ya rear+1==front
    bool isfull() {
        if ((rear == size - 1 && front == 0) || (rear == front - 1)) {
            return true;
        } else {
            return false;
        }
    }

    // ── isempty: koi element nahi? ───────────────────────────────────────────
    bool isempty() {
        if (front == -1 && rear == -1) {
            return true;
        } else {
            return false;
        }
    }

    // ── pushrear: rear end pe insert (enqueue) ───────────────────────────────
    void pushrear(int data) {
        if (isfull()) {
            cout << "overflow" << endl;
        } else if (rear == size - 1 && front != 0) {
            rear = 0;                        // circular wrap — array ke start
            arr[rear] = data;
        } else {
            if (front == -1) {
                front = 0;                   // pehla element — front set
            }
            rear++;
            arr[rear] = data;                // rear pe enqueue
        }
    }

    // ── popfront: front se remove (dequeue) ─────────────────────────────────
    void popfront() {
        if (isempty()) {
            cout << "underflow" << endl;
        } else if (front == rear) {
            arr[front] = -1;
            front = -1;
            rear = -1;                     // ek hi element tha — empty
        } else if (front == size - 1) {
            arr[front] = -1;
            front = 0;                     // circular wrap front
        } else {
            arr[front] = -1;
            front++;                       // normal dequeue — front aage
        }
    }

    // ── pushfront: front end pe insert ───────────────────────────────────────
    void pushfront(int data) {
        if (isfull()) {
            cout << "overflow" << endl;
        } else if (front == -1 && rear == -1) {
            front = rear = 0;
            arr[front] = data;
        } else if (front == 0 && rear != size - 1) {
            front = size - 1;              // circular wrap — peeche se front
            arr[front] = data;
        } else {
            front--;
            arr[front] = data;
        }
    }

    // ── poprear: rear end se remove ───────────────────────────────────────────
    void poprear() {
        if (isempty()) {
            cout << "underflow" << endl;
        } else if (rear == front) {
            arr[rear] = -1;
            rear = -1;
            front = -1;
        } else if (rear == 0) {
            rear = size - 1;               // circular wrap rear
        } else {
            arr[rear] = -1;
            rear--;
        }
    }

    // ── print: front/rear pointers aur array ─────────────────────────────────
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
    DEqueue *deq = new DEqueue(5);
    deq->print();
    deq->pushrear(10);
    deq->print();
    deq->pushfront(20);
    deq->print();
    deq->pushfront(70);
    deq->print();
    deq->pushrear(50);
    deq->print();
    deq->pushfront(30);
    deq->print();
    deq->popfront();
    deq->print();
    deq->popfront();
    deq->print();
    deq->popfront();
    deq->popfront();
    deq->print();
}
