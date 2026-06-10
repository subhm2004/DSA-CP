/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_practice_2.cpp
 * PROBLEM  : Stack Practice 2
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STACK RECURSION PRACTICE — middle, bottom insert, reverse, sort
// ────────────────────────────────────────────────────────────────────────────
// recursion + pop/push trick — stack order preserve karte hue manipulate
// sort: pop sab, insertinstack se sorted order mein wapas daalo
// ════════════════════════════════════════════════════════════════════════════

// ── getmiddle: recursive middle element print ───────────────────────────────
//   1) size==mid → top print (base)
//   2) pop, size--, recurse
//   3) wapas aate waqt temp push — restore
void getmiddle(stack<int> &sp, int &size, int &mid) {
    if (size == mid) {
        cout << sp.top() << endl;
        return;
    }
    int temp = sp.top();
    sp.pop();                              // unwind — ek element hatao
    size--;
    getmiddle(sp, size, mid);
    sp.push(temp);                         // rewind — element wapas
}

// ── insertatbottom: element stack ke bottom pe daalo ───────────────────────
//   1) empty → element push (base)
//   2) pop top, recurse, phir temp push
void insertatbottom(stack<int> &sp, int &element) {
    if (sp.empty()) {
        sp.push(element);                  // base — bottom pe daal diya
        return;
    }
    int temp = sp.top();
    sp.pop();
    insertatbottom(sp, element);
    sp.push(temp);
}

// ── reversestack: pura stack reverse karo ─────────────────────────────────
//   1) top pop, recurse
//   2) wapas aate waqt insertatbottom — ulta order
void reversestack(stack<int> &sp) {
    if (sp.empty()) {
        return;
    }
    int temp = sp.top();
    sp.pop();
    reversestack(sp);
    insertatbottom(sp, temp);
}

// ── insertinstack: sorted order maintain karte hue insert ──────────────────
//   1) empty ya top < element → push
//   2) warna pop, recurse, temp push
void insertinstack(stack<int> &sp, int &element) {
    if (sp.empty() || sp.top() < element) {
        sp.push(element);
        return;
    }
    int temp = sp.top();
    sp.pop();
    insertinstack(sp, element);
    sp.push(temp);
}

// ── sortstack: recursion se stack sort karo ─────────────────────────────────
//   1) top pop, baaki sort karo (recurse)
//   2) popped element ko sorted position mein insert
void sortstack(stack<int> &sp) {
    if (sp.empty()) {
        return;
    }
    int temp = sp.top();
    sp.pop();
    sortstack(sp);
    insertinstack(sp, temp);
}

int main() {
    stack<int> sp;
    sp.push(9);
    sp.push(8);
    sp.push(5);
    sp.push(12);
    sp.push(10);
    int size = sp.size();
    int mid;
    if (size & 1) {
        mid = sp.size() / 2 + 1;
    } else {
        mid = sp.size() / 2;
    }
    int element;
    sortstack(sp);

    for (int i = 0; i < size; i++) {
        cout << sp.top() << endl;
        sp.pop();                          // sorted stack print
    }
}
