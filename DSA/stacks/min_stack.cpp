/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : min_stack.cpp
 * PROBLEM  : Min Stack
 * LEETCODE : 155 — Min Stack
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MIN STACK — O(1) mein minimum element bhi return karo
// ────────────────────────────────────────────────────────────────────────────
// har entry pair {value, minSoFar} — push pe running min track
// pop/top/min sab O(1) — extra space for min history
// ════════════════════════════════════════════════════════════════════════════

class minStack {
    vector<pair<int, int>> sp;

    // ── push: value + current min store karo ─────────────────────────────────
    //   1) empty → {data, data} push
    //   2) warna min(prevMin, data) ke saath push
    void push(int data) {
        if (sp.empty()) {
            pair<int, int> p;
            p.first = data;
            p.second = data;             // pehla element hi min bhi
            sp.push_back(p);
        } else {
            pair<int, int> p;
            int prevmin = sp.back().second;
            p.second = min(prevmin, data); // running minimum track
            p.first = data;
            sp.push_back(p);
        }
    }

    // ── pop: top element hatao ───────────────────────────────────────────────
    void pop() {
        if (!sp.empty()) {
            sp.pop_back();                 // pair hatao — min auto update
        }
    }

    // ── topvalue: current top element ──────────────────────────────────────────
    int topvalue() {
        if (!sp.empty()) {
            return sp.back().first;
        }
    }

    // ── getmin: stack ka minimum element O(1) ────────────────────────────────
    int getmin() {
        if (!sp.empty()) {
            return sp.back().second;       // stored min — turant mil jayega
        }
    }
};

int main() {
}
