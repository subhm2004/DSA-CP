/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : online_stock_span.cpp
 * PROBLEM  : Online Stock Span
 * LEETCODE : 901 — Online Stock Span
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <utility>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ONLINE STOCK SPAN — consecutive days jahan price <= aaj ki price
// ────────────────────────────────────────────────────────────────────────────
// monotonic decreasing stack of (price, span) pairs
// chhoti prices pop → unka span add; naya pair push
// ════════════════════════════════════════════════════════════════════════════

stack<pair<int, int>> st;

// ── next: nayi price ka span return karo ───────────────────────────────────
//   1) span=1 (aaj ka din)
//   2) stack top price <= current → pop, span += popped span
//   3) {price, span} push
//   4) span return
int next(int price) {
    int span = 1;
    while (!st.empty() && st.top().first <= price) {
        span = span + st.top().second;     // purane din ka span jodo
        st.pop();                          // chhoti/equal price hatao
    }
    st.push({price, span});                // current day record
    return span;
}

int main() {
    int price;
    cin >> price;
    int ans = next(price);
    cout << ans;
}
