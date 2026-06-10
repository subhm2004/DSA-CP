/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : merge_sort_variant.cpp
 * PROBLEM  : Merge Sort Variant
 * ABOUT    : Comparison-based sorting algorithms
 * APPROACH : Divide, sort halves recursively, merge sorted halves.
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE SORT (Class-based) — OOP variant with single temp array merge
// ────────────────────────────────────────────────────────────────────────────
// MergeSort class — merge, mergeSort, sort public API
// Ek temp array me merge — copy back to original
// Same divide-conquer logic, cleaner encapsulation
// ════════════════════════════════════════════════════════════════════════════

class MergeSort
{
public:
    
    // ── merge: [low,mid] aur [mid+1,high] merge — ek temp array ───────────────
    //   1) left/right pointers se chhota element temp me
    //   2) leftover copy
    //   3) temp se arr me copy back
    void merge(int *arr, int low, int mid, int high)
    {
        int n = high - low + 1;
        int *temp = new int[n];
        int left = low, right = mid + 1, idx = 0;

        while (left <= mid && right <= high)
        {
            if (arr[left] <= arr[right])
                temp[idx++] = arr[left++];
            else
                temp[idx++] = arr[right++];
        }

        while (left <= mid)
            temp[idx++] = arr[left++];
        while (right <= high)
            temp[idx++] = arr[right++];

        for (int i = 0; i < n; ++i)
            arr[low + i] = temp[i];

        delete[] temp; // free memory
    }

    // ── mergeSort: recursively divide aur sort ────────────────────────────────
    //   1) low>=high base
    //   2) mid split, dono halves sort
    //   3) merge call
    void mergeSort(int *arr, int low, int high)
    {
        if (low >= high)
            return;

        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }

    // ── sort: public API — array size se sort start ───────────────────────────
    void sort(int *arr, int n)
    {
        mergeSort(arr, 0, n - 1);
    }
};

// ── main: class-based merge sort demo ─────────────────────────────────────────
int main()
{
    int arr[] = {5, 3, 8, 4, 2, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    MergeSort sorter;
    sorter.sort(arr, n);

    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
