/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : merge_sort_practice.cpp
 * PROBLEM  : Merge Sort Practice
 * ABOUT    : General practice and mixed problems
 * APPROACH : Divide, sort halves recursively, merge sorted halves.
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



/*
 * merge()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int> &arr, int low, int mid, int high
 * Returns : void
 */
void merge(vector<int> &arr, int low, int mid, int high)
{
    vector<int> temp;
    int i = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid)
        temp.push_back(arr[i++]);
    while (j <= high)
        temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[low + k] = temp[k];
}



/*
 * mergeSort()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int> &arr, int low, int high
 * Returns : void
 */
void mergeSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);      // Sort left half
    mergeSort(arr, mid + 1, high); // Sort right half
    merge(arr, low, mid, high);    // Merge both halves
}



/*
 * main()
 * Purpose : Entry point — demo/test for Merge Sort Practice
 */
int main()
{
    vector<int> arr = {9, 1, 4, 14, 4, 15, 6};
    int n = arr.size();

    cout << "Before sorting: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    mergeSort(arr, 0, n - 1);

    cout << "After sorting: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n";

    return 0;
}
