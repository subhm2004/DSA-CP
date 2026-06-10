/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : sliding_window_maximum.cpp
 * PROBLEM  : Sliding Window Maximum
 * LEETCODE : 239 — Sliding Window Maximum
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : Deque/map maintains window min/max in O(n).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <deque>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SLIDING WINDOW FIRST NEGATIVE — deque se window negatives track
// ────────────────────────────────────────────────────────────────────────────
// deque mein negative indices store — front = window ka pehla negative
// window slide → purane index bahar, naye negative push_back
// ════════════════════════════════════════════════════════════════════════════

// ── printfirstnegative: har window ka pehla negative print ─────────────────
//   1) pehli window (size k) ke negatives deque mein
//   2) har slide: front expired? pop_front
//   3) naya negative → push_back index
//   4) deque.front() se answer print
void printfirstnegative(int *arr, int &size, int &k) {
    deque<int> dq;                         // negative element ke indices
    for (int i = 1; i <= k; i++) {
        if (arr[i] < 0) {
            dq.push_back(i);               // negative index store
        }
    }
    for (int i = k + 1; i <= size; i++) {
        if (dq.empty()) {
            cout << 0 << " ";
        } else {
            cout << arr[dq.front()] << " "; // window ka pehla negative
        }
        if (i - dq.front() >= k) {
            dq.pop_front();                // window se bahar — index hatao
        }
        if (arr[i] < 0) {
            dq.push_back(i);               // naya negative window mein
        }
    }
    if (dq.empty()) {
        cout << 0 << " ";
    } else {
        cout << arr[dq.front()] << " ";
    }
}

int main() {
    int arr[] = {2, -5, 4, -1, -2, 0, 5};
    int size = 7;
    int k = 3;                             // window size
    printfirstnegative(arr, size, k);
}
