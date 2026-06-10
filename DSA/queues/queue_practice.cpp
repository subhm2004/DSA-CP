/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : queue_practice.cpp
 * PROBLEM  : Queue Practice
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DOUBLE ENDED QUEUE (DEQueue) — circular array se front/rear dono ends
// ────────────────────────────────────────────────────────────────────────────
// circular wrap: rear==size-1 → rear=0; front==0 → front=size-1
// full: (rear==size-1 && front==0) || (rear+1==front)
// ════════════════════════════════════════════════════════════════════════════

class DEQueue {
public:
    int *arr;
    int front;
    int rear;
    int size;
    DEQueue(int s) {
        this->size = s;
        this->front = -1;
        this->rear = -1;
        arr = new int[size];
    }

    // ── pushback: rear se enqueue ────────────────────────────────────────────
    //   1) overflow check — circular full condition
    //   2) pehla element → front=0, rear++
    //   3) rear wrap ya normal rear++
    void pushback(int data) {
        if ((rear == size - 1 && front == 0) || (rear + 1 == front)) {
            cout << "Queue Overflow" << endl;
        } else if (front == -1) {
            front = 0;
            rear++;
            arr[rear] = data;              // pehla element — rear pe daalo
        } else if (front != 0 && rear == size - 1) {
            rear = 0;                        // circular wrap — end se start
            arr[rear] = data;
        } else {
            rear++;
            arr[rear] = data;
        }
    }

    // ── popfront: front se dequeue ───────────────────────────────────────────
    //   1) underflow check
    //   2) single element → reset front/rear=-1
    //   3) front wrap ya front++
    void popfront() {
        if (front == -1 && rear == -1) {
            cout << "Queue underflow" << endl;
        } else if (front == rear) {
            arr[front] = -1;
            front = -1;
            rear = -1;                     // last element — queue empty
        } else if (front == size - 1) {
            arr[front] = -1;
            front = 0;                     // circular wrap — start pe aao
        } else {
            arr[front] = -1;
            front++;
        }
    }

    // ── popback: rear se element hatao ───────────────────────────────────────
    void popback() {
        if (front == -1 && rear == -1) {
            cout << "Queue Overflow" << endl;
        } else if (front == rear) {
            arr[rear] = -1;
            rear = -1;
            front = -1;
        } else if (rear == 0) {
            arr[rear] = -1;
            rear = size - 1;               // circular wrap — end pe jao
        } else {
            arr[rear] = -1;
            rear--;
        }
    }

    // ── pushfront: front se insert ───────────────────────────────────────────
    void pushfront(int data) {
        if ((front == 0 && rear == size - 1) || (rear + 1 == front)) {
            cout << "Queue Overflow" << endl;
        } else if (front == -1 && rear == -1) {
            front++;
            rear++;
            arr[front] = data;
        } else if (front == 0 && rear != size - 1) {
            front = size - 1;              // circular wrap — peeche se front
            arr[front] = data;
        } else {
            front--;
            arr[front] = data;
        }
    }
};

int main() {
}
