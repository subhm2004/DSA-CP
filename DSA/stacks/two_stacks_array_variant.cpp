/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : two_stacks_array_variant.cpp
 * PROBLEM  : Two Stacks Array Variant
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO STACKS IN ARRAY (VARIANT) — left/right growth with cleanup on pop
// ────────────────────────────────────────────────────────────────────────────
// top1 left se badhta, top2 right se ghata
// pop pe arr[index]=-1 mark — slot free visual
// ════════════════════════════════════════════════════════════════════════════

class Stack {
public:
    int *arr;
    int size;
    int top1;
    int top2;
    Stack(int size) {
        this->size = size;
        this->arr = new int[size];
        this->top1 = -1;
        this->top2 = size;
    }

    // ── isempty1: left stack khali? ──────────────────────────────────────────
    bool isempty1() {
        if (top1 == -1) {
            cout << "stack1 is empty" << endl;
            return true;
        } else {
            return false;
        }
    }

    // ── isempty2: right stack khali? ─────────────────────────────────────────
    bool isempty2() {
        if (top2 == size) {
            cout << "stack2 is empty" << endl;
            return true;
        } else {
            return false;
        }
    }

    // ── isfull: dono stacks touch ho gaye? ───────────────────────────────────
    bool isfull() {
        if (top2 - top1 == 1) {
            return true;
        } else {
            return false;
        }
    }

    // ── push1: left stack mein push ──────────────────────────────────────────
    void push1(int data) {
        if (isfull()) {
            cout << "stack is full, can't push" << endl;
            return;
        } else {
            top1++;
            arr[top1] = data;              // left grow — index badhao
        }
    }

    // ── push2: right stack mein push ─────────────────────────────────────────
    void push2(int data) {
        if (isfull()) {
            cout << "stack is full, can't push" << endl;
            return;
        } else {
            top2--;
            arr[top2] = data;              // right grow — index ghatao
        }
    }

    // ── pop1: left stack se pop ──────────────────────────────────────────────
    void pop1() {
        if (isempty1()) {
            cout << "stack is empty, can't delete " << endl;
            return;
        } else {
            arr[top1] = -1;                // slot mark free
            top1--;
        }
    }

    // ── pop2: right stack se pop ─────────────────────────────────────────────
    void pop2() {
        if (isempty2()) {
            cout << "stack is empty, can't delete" << endl;
            return;
        } else {
            arr[top2] = -1;
            top2++;                        // right shrink
        }
    }

    // ── print: array state ───────────────────────────────────────────────────
    void print() {
        cout << "top1: " << top1 << endl;
        cout << "top2: " << top2 << endl;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack sp(8);
    sp.push1(10);
    sp.push1(20);
    sp.push2(30);
    sp.push2(40);
    sp.pop1();
    sp.pop2();
    sp.pop1();
    sp.pop1();
    sp.print();
}
