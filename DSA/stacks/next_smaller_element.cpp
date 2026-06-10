/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : next_smaller_element.cpp
 * PROBLEM  : Next Smaller Element
 * LEETCODE : 496 — Next Greater Element I
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
// NEXT SMALLER ELEMENT — right side pe pehla chhota element
// ────────────────────────────────────────────────────────────────────────────
// right-to-left scan; monotonic stack of candidates
// stack top < arr[i] → answer; warna pop karke dhundho
// ════════════════════════════════════════════════════════════════════════════

// ── nextsmaller: har index ka next smaller element ─────────────────────────
//   1) right se left — index start = size-1
//   2) stack top < arr[index] → ans[index]=top, push arr[index]
//   3) top >= arr[index] → pop
//   4) stack empty → ans[index]=-1
void nextsmaller(int ans[], int &index, int &size, int arr[], stack<int> &sp) {
    while (index >= 0) {
        if (!sp.empty() && (sp.top() < arr[index])) {
            ans[index] = sp.top();
            sp.push(arr[index]);           // monotonic — current push
            index--;
        } else if (!sp.empty() && (sp.top() > arr[index])) {
            sp.pop();                      // bada element — useless hatao
        } else {
            ans[index] = -1;
        }
    }
}

int main() {
    int arr[] = {8, 4, 1, 6, 2, 3};
    int size = 6;
    int index = size - 1;
    int ans[6];
    stack<int> sp;
    sp.push(-1);                           // sentinel base
    nextsmaller(ans, index, size, arr, sp);
    for (int i = 0; i < size; i++) {
        cout << ans[i] << " ";
    }
}
