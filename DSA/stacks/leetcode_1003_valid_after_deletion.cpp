/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : leetcode_1003_valid_after_deletion.cpp
 * PROBLEM  : Leetcode 1003 Valid After Deletion
 * LEETCODE : 1003 — Check If String Is Deletable
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// VALID STRING AFTER DELETION — "abc" pattern repeatedly hatao
// ────────────────────────────────────────────────────────────────────────────
// jab tak "abc" milta hai erase karo; end mein empty → valid
// stack ki tarah greedy deletion — leftmost "abc" hatao
// ════════════════════════════════════════════════════════════════════════════

// ── validstr: repeated "abc" deletion se string valid hai? ──────────────────
//   1) jab tak str mein "abc" hai — find karke erase
//   2) "abc" nahi mila aur str non-empty → false
//   3) str empty ho gayi → true
//   4) warna false
bool validstr(string str, string &substr) {
    while (!str.empty()) {
        if (str.find(substr) == string::npos) {
            return false;
        } else {
            int index = str.find(substr);
            str.erase(index, 3);           // "abc" pattern delete — 3 chars
        }
    }
    if (str.empty()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    string str = "ababcc";
    string substr = "abc";
    bool ans = validstr(str, substr);
    cout << ans << endl;
}
