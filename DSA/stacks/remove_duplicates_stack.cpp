/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : remove_duplicates_stack.cpp
 * PROBLEM  : Remove Duplicates Stack
 * LEETCODE : 1047 — Remove All Adjacent Duplicates In String
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REMOVE ADJACENT DUPLICATES — stack se same chars cancel karo
// ────────────────────────────────────────────────────────────────────────────
// char aaye → top same hai to pop, warna push
// end mein stack reverse karke print — original order
// ════════════════════════════════════════════════════════════════════════════

// ── reversestack: stack ko print order mein dikhao ─────────────────────────
//   1) temp stack mein sab transfer — LIFO reverse
//   2) temp se print karte hue pop
void reversestack(stack<char> &st) {
    stack<char> sp;
    while (!st.empty()) {
        sp.push(st.top());                 // transfer — order reverse hoga
        st.pop();
    }
    while (!sp.empty()) {
        cout << sp.top();
        sp.pop();
    }
}

// ── removeduplicates: adjacent same chars hatao ────────────────────────────
//   1) pehla char push
//   2) agla char: top same → pop (cancel), warna push
//   3) end tak scan
//   4) result stack print
void removeduplicates(string &str, stack<char> &st) {
    int i = 0;
    st.push(str[i]);
    i++;
    while (i < str.length()) {
        if (!st.empty() && str[i] == st.top()) {
            st.pop();                      // duplicate — cancel karo
        } else {
            st.push(str[i]);               // naya char — stack pe rakho
        }
        i++;
    }
    reversestack(st);
}

int main() {
    string str = "azxxzy";
    stack<char> st;
    removeduplicates(str, st);
}
