/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : valid_parentheses.cpp
 * PROBLEM  : Valid Parentheses
 * LEETCODE : 20 — Valid Parentheses
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// VALID PARENTHESES — brackets properly match ho rahe hain?
// ────────────────────────────────────────────────────────────────────────────
// opening → push; closing → top match kare to pop, warna false
// end mein stack empty hona chahiye
// ════════════════════════════════════════════════════════════════════════════

// ── checkparenthesis: bracket string valid hai? ────────────────────────────
//   1) opening bracket → stack push
//   2) closing bracket → top matching opening? pop : return false
//   3) end tak scan
//   4) stack empty → true, warna false
bool checkparenthesis(string &str) {
    int i = 0;
    stack<char> sp;
    while (i < str.length()) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            sp.push(str[i]);               // opening — stack pe push
        } else if (str[i] == ')') {
            if (sp.top() == '(' && !sp.empty()) {
                sp.pop();                  // match — pop karo
            } else {
                return false;
            }
        } else if (str[i] == '}' && !sp.empty()) {
            if (sp.top() == '{') {
                sp.pop();
            } else {
                return false;
            }
        } else if (str[i] == ']' && !sp.empty()) {
            if (sp.top() == '[') {
                sp.pop();
            } else {
                return false;
            }
        } else {
            return false;
        }
        i++;
    }
    if (sp.empty()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    string str = "[{()}]";
    int n = str.length();
    bool ans = checkparenthesis(str);
    cout << ans << endl;
}
