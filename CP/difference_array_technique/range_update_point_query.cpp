/*
 * ============================================================================
 * TOPIC    : Difference Array Technique
 * FILE     : range_update_point_query.cpp
 * PROBLEM  : Multiple range add updates, then point query
 * APPROACH : Difference array + prefix on demand
 * COMPLEX  : Update O(1), Point query O(n) once after all updates
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class DiffArray {
    vector<long long> diff;
    int n;

public:
    DiffArray(int n) : n(n), diff(n + 1, 0) {}

    void rangeAdd(int l, int r, long long val) {
        diff[l] += val;
        if (r + 1 < n)
            diff[r + 1] -= val;
    }

    long long valueAt(int i) const {
        long long sum = 0;
        for (int j = 0; j <= i; j++)
            sum += diff[j];
        return sum;
    }

    vector<long long> buildFinalArray() const {
        vector<long long> arr(n);
        long long cur = 0;
        for (int i = 0; i < n; i++) {
            cur += diff[i];
            arr[i] = cur;
        }
        return arr;
    }
};

int main() {
    DiffArray da(6);
    da.rangeAdd(1, 3, 5);
    da.rangeAdd(2, 5, 2);
    da.rangeAdd(0, 0, 10);

    cout << "Point query index 2 = " << da.valueAt(2) << endl;
    cout << "Final array: ";
    for (long long x : da.buildFinalArray())
        cout << x << " ";
    cout << endl;
    return 0;
}
