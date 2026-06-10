/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : reverse_stack.cpp
 * PROBLEM  : Reverse Stack
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REVERSE STACK — recursion se stack ulta karo
// ────────────────────────────────────────────────────────────────────────────
// pop sab → recurse → insertatbottom se wapas daalo
// bottom insert trick — reversed order maintain
// ════════════════════════════════════════════════════════════════════════════

// ── insertatbottom: element bottom pe daalo (recursive) ────────────────────
//   1) empty → push element
//   2) pop, recurse, temp push
void insertatbottom(stack<int> &sp, int &temp, int &element) {
    if (sp.empty()) {
        sp.push(element);
        return;
    }
    sp.pop();
    insertatbottom(sp, sp.top(), element);
    sp.push(temp);                         // restore stack order
}

// ── reversestack: pura stack reverse ─────────────────────────────────────────
//   1) top pop, recurse
//   2) wapas aate waqt insertatbottom
void reversestack(stack<int> &sp, int &temp, int &element) {
    if (sp.empty()) {
        return;
    }
    sp.pop();
    reversestack(sp, sp.top(), element);
    insertatbottom(sp, temp, temp);
}

int main() {
    stack<int> sp;
    sp.push(10);
    sp.push(20);
    sp.push(30);
    sp.push(40);
    sp.push(50);
    int temp = sp.top();
    int element = sp.top();
    reversestack(sp, temp, element);
    while (!sp.empty()) {
        cout << sp.top() << endl;
        sp.pop();                          // reversed stack print
    }
}
