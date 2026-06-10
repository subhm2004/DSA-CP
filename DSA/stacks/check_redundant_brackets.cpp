/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : check_redundant_brackets.cpp
 * PROBLEM  : Check Redundant Brackets
 * LEETCODE : 678 — Valid Parenthesis String
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REDUNDANT BRACKETS — kya expression mein extra () hai bina operator ke?
// ────────────────────────────────────────────────────────────────────────────
// ')' pe stack se operators count — agar 0 operators → redundant brackets
// '(' aur operators push; ')' pe sab operators pop karo
// ════════════════════════════════════════════════════════════════════════════

// ── redundantbracket: extra parentheses detect karo ────────────────────────
//   1) '(' ya operator → stack push
//   2) ')' aaye → operators count karo jab tak '(' na mile
//   3) count==0 → redundant (koi operator nahi tha)
//   4) '(' pop karke aage badho
bool redundantbracket(string &str, stack<char> &sp) {
    int count = 0;
    int index = 0;
    while (index < str.length()) {
        if (str[index] == '(' || str[index] == '+' || str[index] == '*' ||
            str[index] == '-' || str[index] == '/') {
            sp.push(str[index]);           // operator ya '(' — stack pe push
        }
        if (str[index] == ')') {
            count = 0;
            while (!sp.empty() && sp.top() != '(') {
                if (sp.top() == '+' || sp.top() == '*' || sp.top() == '-' ||
                    sp.top() == '/') {
                    count++;
                    sp.pop();              // operator pop — expression ke andar
                }
            }
            if (count == 0) {
                return true;               // koi operator nahi — redundant ()
            }

            sp.pop();                      // matching '(' pop
        }
        index++;
    }
    if (count != 0) {
        return false;
    }
}

int main() {
    string str = "((a+b)*((c)+d))";
    stack<char> sp;
    bool ans = redundantbracket(str, sp);
    cout << ans << endl;
}
