/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : queue_array_implementation.cpp
 * PROBLEM  : Queue Array Implementation
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LINEAR QUEUE (ARRAY) — front/rear pointers, non-circular
// ────────────────────────────────────────────────────────────────────────────
// front=-1, rear=-1 initially empty
// enqueue: rear++, pehla element pe front=0 set
// dequeue: front++, single element pe reset -1
// ════════════════════════════════════════════════════════════════════════════

class Queue {
public:
    int *arr;
    int size;
    int front;
    int rear;
    Queue(int s) {
        this->size = s;
        this->front = -1;
        this->rear = -1;
        arr = new int[size];
    }

    // ── isfull: rear end pe pahunch gaye? ────────────────────────────────────
    bool isfull() {
        if (rear == size - 1) {
            return true;
        } else {
            return false;
        }
    }

    // ── isempty: front/rear dono -1? ─────────────────────────────────────────
    bool isempty() {
        if (front == -1 && rear == -1) {
            return true;
        } else {
            return false;
        }
    }

    // ── push: rear se enqueue ────────────────────────────────────────────────
    void push(int data) {
        if (isfull()) {
            cout << "queue overflow" << endl;
        } else {
            rear++;
            if (front == -1) {
                front = 0;                   // pehla element — front set karo
            }
            arr[rear] = data;                // rear pe data daalo
        }
    }

    // ── pop: front se dequeue ────────────────────────────────────────────────
    void pop() {
        if (isempty()) {
            cout << "queue underflow" << endl;
        } else {
            if (front == rear) {
                front = -1;
                rear = -1;                 // ek element — queue empty
            } else {
                arr[front] = 0;
                front++;                   // front aage — FIFO dequeue
            }
        }
    }

    // ── getfront: peek front element ─────────────────────────────────────────
    int getfront() {
        if (!isempty()) {
            return arr[front];
        }
    }

    // ── getrear: peek rear element ───────────────────────────────────────────
    int getrear() {
        if (!isempty()) {
            return arr[rear];
        }
    }

    // ── printqueue: front/rear aur array print ───────────────────────────────
    void printqueue() {
        cout << "front is: " << front << endl;
        cout << "rear is: " << rear << endl;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
};

int main() {
    Queue *q = new Queue(8);
    q->push(10);
    q->push(20);
    q->push(30);
    q->printqueue();
    cout << endl;
    q->push(40);
    q->push(50);
    q->printqueue();
    cout << endl;
    q->pop();
    q->printqueue();
}
