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



/*
 * find_kth_smallest()
 * Purpose : Min heap or quickselect for k-th statistic.
 * Params  : int arr[], int k, int n
 * Returns : int
 */
int find_kth_smallest(int arr[], int k, int n) {
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int i = 0; i < n; i++) {
        min_heap.push(arr[i]);
    }

    for (int i = 1; i < k; i++) {
        min_heap.pop();
    }

    return min_heap.top();
}



/*
 * main()
 * Purpose : Entry point — demo/test for Kth Smallest Using Min Heap
 */
int main() {
    int arr[] = {3, 2, 9, 7, 6, 5, 1, 8};
    int n = 8;
    int k = 4;

    int ans = find_kth_smallest(arr, k, n);
    cout << "K-th smallest element: " << ans << endl;

    return 0;
}
