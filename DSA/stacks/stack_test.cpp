/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_test.cpp
 * PROBLEM  : Stack Test
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// OCTAL LITERAL TEST — leading zero wala number octal ban jata hai
// ────────────────────────────────────────────────────────────────────────────
// 0647 octal hai → decimal 423 print hoga
// ════════════════════════════════════════════════════════════════════════════

// ── main: octal vs decimal demo ─────────────────────────────────────────────
//   1) 0647 octal literal assign
//   2) cout se decimal value print
int main() {
    int a = 0647;                          // octal — leading 0 matlab base-8
    cout << a << endl;
    return 0;
}
