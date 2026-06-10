/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_basics.cpp
 * PROBLEM  : Stack Basics
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STACK MIDDLE ELEMENT — recursion se stack ka middle nikaalo
// ────────────────────────────────────────────────────────────────────────────
// LIFO: top se pop karo, base pe print, wapas push — order preserve
// odd size → (n/2)+1 wala element; even → n/2 wala
// ════════════════════════════════════════════════════════════════════════════

// ── findmid: recursive middle element print ─────────────────────────────────
//   1) base case: position==1 → current temp print karo
//   2) top pop karo — stack se ek element hatao
//   3) position-1 ke saath recurse — andar jaate jao
//   4) wapas aate waqt temp push — stack restore karo
void findmid(stack<int> &sp, int temp, int position) {
    if (position == 1) {
        cout << temp << endl;
        return;
    }
    sp.pop();                              // stack se top hatao — LIFO unwind
    findmid(sp, sp.top(), position - 1);
    sp.push(temp);                         // restore — element wapas stack pe
}

// ── main: stack middle demo ─────────────────────────────────────────────────
//   1) values push karo stack mein
//   2) odd/even size se middle position decide
//   3) findmid se middle print
int main() {
    stack<int> sp;
    sp.push(10);                           // push — stack top pe add
    sp.push(20);
    sp.push(30);
    sp.push(40);
    sp.push(50);
    sp.push(60);
    int position;
    int temp = sp.top();
    if (sp.size() & 1) {
        position = sp.size() / 2 + 1;
    } else {
        position = sp.size() / 2;
    }
    findmid(sp, temp, position);
}
