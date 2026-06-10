/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : previous_smaller_element.cpp
 * PROBLEM  : Previous Smaller Element
 * LEETCODE : 503 — Next Greater Element II
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PREVIOUS SMALLER ELEMENT — left side pe pehla chhota element
// ────────────────────────────────────────────────────────────────────────────
// left-to-right scan; monotonic increasing stack
// stack top < arr[i] → answer; warna pop
// ════════════════════════════════════════════════════════════════════════════

// ── prevsmallerelement: har index ka previous smaller ──────────────────────
//   1) left se right scan
//   2) stack top < arr[index] → ans push, current push
//   3) warna pop — chhota dhundho
void prevsmallerelement(int arr[], int &index, int &size) {
    stack<int> sp;
    vector<int> ans;
    sp.push(-1);                           // sentinel — left mein koi nahi
    while (index < size) {
        if (!sp.empty() && (sp.top() < arr[index])) {
            ans.push_back(sp.top());
            sp.push(arr[index]);           // monotonic stack maintain
            index++;
        } else {
            sp.pop();                      // bada/equal — hatao
        }
    }
}

int main() {
    int arr[] = {8, 4, 6, 1, 2, 3};
    int size = 6;
    int index = 0;
}
