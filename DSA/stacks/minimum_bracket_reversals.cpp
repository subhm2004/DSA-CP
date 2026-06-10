/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : minimum_bracket_reversals.cpp
 * PROBLEM  : Minimum Bracket Reversals
 * LEETCODE : 1249 — Minimum Remove to Make Valid Parentheses
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MINIMUM BRACKET REVERSALS — {} pairs ko valid banane ke liye kitni flip
// ────────────────────────────────────────────────────────────────────────────
// odd length → impossible (-1)
// stack se unmatched brackets nikaalo, pairs count karke reversals estimate
// ════════════════════════════════════════════════════════════════════════════

// ── reversalcount: minimum reversals to balance braces ──────────────────────
//   1) odd length check → -1 return
//   2) scan: '{' push, '}' match ho to pop warna push
//   3) stack mein bache unmatched — pairs banao
//   4) same-same pair → 1 reversal; opposite pair → 2 reversals
int reversalcount(string &str) {
    stack<char> st;
    if (str.length() & 1) {
        return -1;                         // odd length — valid balance impossible
    } else {
        int i = 0;
        while (i < str.length()) {
            if (str[i] == '{') {
                st.push(str[i]);             // opening brace — stack pe push
            } else {
                if (st.empty())
                    st.push(str[i]);
                else {
                    if (st.top() == '{') {
                        st.pop();             // match — pop karo
                    } else {
                        st.push(str[i]);
                    }
                }
            }
            i++;
        }
    }
    int op_count = 0;
    if (!st.empty()) {
        while (!st.empty()) {
            int temp = st.top();
            st.pop();
            if ((st.top() == '}' && temp == '}') || (st.top() == '{' && temp == '{')) {
                op_count++;
                st.pop();
            } else if (temp == '}' && st.top() == '{' || (temp == '{' && st.top() == '}')) {
                op_count = op_count + 2;
                st.pop();
            }
        }
        return op_count;
    } else {
        return 0;
    }
}

int main() {
    string str = "{}}{{{";
    int ans = reversalcount(str);
    cout << ans << endl;
}
