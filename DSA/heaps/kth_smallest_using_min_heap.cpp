/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : kth_smallest_using_min_heap.cpp
 * PROBLEM  : Kth Smallest Using Min Heap
 * LEETCODE : 703 — Kth Largest Element in a Stream
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// K-TH SMALLEST — Min heap se k baar pop karo
// ────────────────────────────────────────────────────────────────────────────
// Saare elements min-heap me daalo -> sabse chhota top pe
// (k-1) baar pop -> k-th smallest top pe bachta hai
// Simple approach: O(n log n) — sab push + k pops
// ════════════════════════════════════════════════════════════════════════════

// ── find_kth_smallest: array ka k-th smallest element ──────────────────────
//   1) min_heap (greater<int>) banao — chhota element top pe
//   2) saare n elements heap me push karo
//   3) (k-1) baar pop karo — chhote elements hatao
//   4) top() = k-th smallest return karo
int find_kth_smallest(int arr[], int k, int n) {
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int i = 0; i < n; i++) {
        min_heap.push(arr[i]);
    }

    for (int i = 1; i < k; i++) {
        min_heap.pop(); // har pop ek chhota element hataata hai
    }

    return min_heap.top();
}

// ── main: sample array pe test ───────────────────────────────────────────────
//   1) arr, n, k set karo
//   2) find_kth_smallest call karke print karo
int main() {
    int arr[] = {3, 2, 9, 7, 6, 5, 1, 8};
    int n = 8;
    int k = 4;

    int ans = find_kth_smallest(arr, k, n);
    cout << "K-th smallest element: " << ans << endl;

    return 0;
}
