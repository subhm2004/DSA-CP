/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : insert_at_bottom_of_stack.cpp
 * PROBLEM  : Insert At Bottom Of Stack
 * LEETCODE : 225 — Implement Stack using Queues
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INSERT AT BOTTOM — element stack ke sabse neeche daalo
// ────────────────────────────────────────────────────────────────────────────
// iterative: aux stack mein transfer, insert, wapas transfer
// recursive: pop sab, base pe insert, wapas push
// ════════════════════════════════════════════════════════════════════════════

// ── insertatbottom: iterative — aux stack se bottom insert ─────────────────
//   1) sp se sab st mein transfer (pop/push)
//   2) element st mein push (bottom position)
//   3) st se sab wapas sp mein
void insertatbottom(stack<int> &sp, stack<int> &st, int &element) {
    while (!sp.empty()) {
        st.push(sp.top());                 // temp stack mein shift
        sp.pop();
    }
    st.push(element);                      // bottom pe naya element
    while (!st.empty()) {
        sp.push(st.top());                 // wapas original stack mein
        st.pop();
    }
}

// ── insertrec: recursive bottom insert ─────────────────────────────────────
//   1) empty → element push (base case)
//   2) pop, recurse, temp push — unwind
void insertrec(stack<int> &sp, int &element, int temp) {
    if (sp.empty()) {
        sp.push(element);
        return;
    }
    sp.pop();
    insertrec(sp, element, sp.top());
    sp.push(temp);                         // restore — element wapas stack pe
}

int main() {
    int element = 5;
    stack<int> sp;
    sp.push(10);
    sp.push(20);
    sp.push(30);
    sp.push(40);
    sp.push(50);
    stack<int> st;
    int temp = sp.top();
    insertatbottom(sp, st, element);
    cout << "Stack is : " << endl;
    while (!sp.empty()) {
        cout << sp.top() << endl;
        sp.pop();
    }
}
