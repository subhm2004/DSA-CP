/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : two_stacks_in_array.cpp
 * PROBLEM  : Two Stacks In Array
 * LEETCODE : 155 — Min Stack (two-stack design pattern)
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO STACKS IN ONE ARRAY — top1 left se, top2 right se grow
// ────────────────────────────────────────────────────────────────────────────
// top1=-1 (left empty), top2=size (right empty)
// full jab top2 == top1+1 — beech mein jagah khatam
// ════════════════════════════════════════════════════════════════════════════

class Stack {
public:
    int *arr;
    int top1;
    int top2;
    int size;
    Stack(int size) {
        this->size = size;
        arr = new int[size];
        this->top1 = -1;                   // stack1 left end — abhi empty
        this->top2 = size;                 // stack2 right end — abhi empty
    }

    // ── isEmpty: dono stacks khali? ─────────────────────────────────────────
    //   1) top1==-1 aur top2==size → true
    bool isEmpty() {
        if (top1 == -1 && top2 == size) {
            return true;
        } else {
            return false;
        }
    }

    // ── isFull: array bhar gaya? ─────────────────────────────────────────────
    //   1) top2 == top1+1 → dono stacks touch ho gaye
    bool isFull() {
        if (top2 == top1 + 1) {
            return true;
        } else {
            return false;
        }
    }

    // ── push1: stack1 (left) mein push ───────────────────────────────────────
    //   1) overflow check
    //   2) top1++ aur arr[top1]=data
    void push1(int data) {
        if (top2 == top1 + 1) {
            cout << "Stack Overflow" << endl;
        } else {
            top1++;                        // left stack grow — index badhao
            arr[top1] = data;
        }
    }

    // ── push2: stack2 (right) mein push ──────────────────────────────────────
    //   1) overflow check
    //   2) top2-- aur arr[top2]=data
    void push2(int data) {
        if (top2 == top1 + 1) {
            cout << "Stack Overflow" << endl;
        } else {
            top2--;                        // right stack grow — index ghatao
            arr[top2] = data;
        }
    }

    // ── pop1: stack1 se pop ──────────────────────────────────────────────────
    //   1) underflow check
    //   2) top1--
    void pop1() {
        if (top1 == -1) {
            cout << "Stack Underflow" << endl;
        } else {
            top1--;                        // left stack shrink
        }
    }

    // ── pop2: stack2 se pop ──────────────────────────────────────────────────
    //   1) underflow check
    //   2) top2++
    void pop2() {
        if (top2 == size) {
            cout << "Stack Underflow" << endl;
        } else {
            top2++;                        // right stack shrink
        }
    }

    // ── gettop1: stack1 ka top element ───────────────────────────────────────
    int gettop1() {
        if (top1 == -1) {
            cout << "Stack1 Underflow" << endl;
            return INT_MIN;
        } else {
            return arr[top1];
        }
    }

    // ── gettop2: stack2 ka top element ───────────────────────────────────────
    int gettop2() {
        if (top2 == size) {
            cout << "Stack2 Underflow" << endl;
            return INT_MIN;
        } else {
            return arr[top2];
        }
    }

    // ── print: array state dikhao ────────────────────────────────────────────
    void print() {
        cout << "Top1: " << top1 << endl;
        cout << "Top2: " << top2 << endl;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack sp(6);
    sp.push1(10);                          // left stack push
    sp.push2(20);                          // right stack push
    sp.push1(30);
    sp.push2(40);
    sp.push1(50);
    sp.push2(60);
    sp.print();
}
