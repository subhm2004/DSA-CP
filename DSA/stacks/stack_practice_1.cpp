/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_practice_1.cpp
 * PROBLEM  : Stack Practice 1
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MONOTONIC STACK — previous / next smaller element
// ────────────────────────────────────────────────────────────────────────────
// stack mein chhote elements rakho; bade aaye to pop karke answer bharo
// sentinel -1 stack base pe — koi smaller nahi mila to -1
// ════════════════════════════════════════════════════════════════════════════

// ── nextsmaller: har index ka next smaller (right side) ─────────────────────
//   1) right se left scan — i = size-1
//   2) stack top < arr[i] → ans[i]=top, push arr[i]
//   3) warna pop — jab tak monotonic order break na ho
//   4) ans array print
void nextsmaller(int arr[], int ans[], int &size) {
    int i = size - 1;
    stack<int> st;
    st.push(-1);                           // sentinel — koi smaller nahi
    while (i >= 0) {
        if (!st.empty() && arr[i] > st.top()) {
            ans[i] = st.top();
            st.push(arr[i]);               // current push — monotonic maintain
            i--;
        } else {
            st.pop();                      // chhota element dhundhne ke liye pop
        }
    }
    cout << "{";
    for (int i = 0; i < size; i++) {
        cout << ans[i] << " ";
    }
    cout << "}";
}

// ── prevsmaller: har index ka previous smaller (left side) ─────────────────
//   1) left se right scan — i = 0
//   2) stack top < arr[i] → ans[i]=top, push arr[i]
//   3) warna pop — monotonic stack property
//   4) ans array print
void prevsmaller(int arr[], int ans[], int &size) {
    int i = 0;
    stack<int> st;
    st.push(-1);
    while (i < size) {
        if (!st.empty() && arr[i] > st.top()) {
            ans[i] = st.top();
            st.push(arr[i]);
            i++;
        } else {
            st.pop();
        }
    }
    cout << "{";
    for (int i = 0; i < size; i++) {
        cout << ans[i] << " ";
    }
    cout << "}";
}

int main() {
    int arr[] = {8, 4, 6, 2, 3};
    int size = 5;
    int ans[5];
    prevsmaller(arr, ans, size);
}
