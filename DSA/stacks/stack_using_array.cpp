/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_using_array.cpp
 * PROBLEM  : Stack Using Array
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STACK USING ARRAY — top pointer se LIFO implement
// ────────────────────────────────────────────────────────────────────────────
// top=-1 empty; push → top++, pop → top--
// overflow jab top==size-1; underflow jab top==-1
// ════════════════════════════════════════════════════════════════════════════

class Stack {
public:
    int *arr;
    int size;
    int top;
    Stack(int size) {
        int *arr = new int[size];
        this->size = size;
        this->top = -1;                    // empty stack — koi element nahi
    }

    // ── push: top pe element daalo ───────────────────────────────────────────
    //   1) top==size-1 → overflow
    //   2) top++, arr[top]=data
    void push(int data) {
        if (top == size - 1) {
            cout << "stack overflow" << endl;
            return;
        } else {
            top = top + 1;                 // index aage — naya top
            arr[top] = data;
        }
    }

    // ── pop: top element nikaalo aur return ──────────────────────────────────
    //   1) top==-1 → underflow
    //   2) value save, top--, return
    int pop() {
        if (top == -1) {
            cout << "stack underflow can't delete" << endl;
            return INT_MIN;
        } else {
            int x = arr[top];
            top = top - 1;                 // shrink — ek element kam
            return x;
        }
    }

    // ── gettop: peek — top element dekho bina hataye ─────────────────────────
    int gettop() {
        if (top == -1) {
            cout << "stack underflow" << endl;
            return INT_MAX;
        } else {
            return arr[top];
        }
    }

    // ── getsize: kitne elements hain ─────────────────────────────────────────
    int getsize() {
        if (top == -1) {
            cout << "Stack is empty" << endl;
        } else {
            return top + 1;                // top index + 1 = count
        }
    }

    // ── isEmpty: stack khali? ────────────────────────────────────────────────
    bool isEmpty() {
        if (top == -1) {
            return true;
        } else {
            return false;
        }
    }

    // ── isfull: array bhar gaya? ─────────────────────────────────────────────
    bool isfull() {
        if (top == size - 1) {
            return true;
        } else {
            return false;
        }
    }

    // ── print: top se bottom tak print ───────────────────────────────────────
    void print() {
        cout << "Stack:" << endl;
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << endl;        // LIFO order — top pehle
        }
    }
};

int main() {
    cout << "Name: Vanshika Aggarwal" << endl;
    cout << "Roll No. 22001003138" << endl;
    Stack *sp = new Stack(5);
    sp->push(10);
    sp->push(20);
    sp->push(30);
    sp->push(40);
    sp->push(50);
    sp->print();
    cout << "Size of stack is: " << sp->getsize() << endl;
    cout << "Is stack full: " << sp->isfull() << endl;
    cout << "popped: " << sp->pop() << " from stack " << endl;
    cout << "New stack is:" << endl;
    sp->print();
}
