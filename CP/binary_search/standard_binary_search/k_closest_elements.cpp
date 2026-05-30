/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : k_closest_elements.cpp
 * PROBLEM  : K closest elements to target in sorted array
 * APPROACH : Two pointers shrink window of size k
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> kClosest(const vector<int> &a, int k, int target) {
    int lo = 0, hi = (int)a.size() - 1;

    while (hi - lo >= k) {
        if (abs(a[lo] - target) > abs(a[hi] - target))
            lo++;
        else
            hi--;
    }

    return vector<int>(a.begin() + lo, a.begin() + lo + k);
}

int main() {
    vector<int> a = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50};
    int k = 4, target = 35;

    for (int x : kClosest(a, k, target))
        cout << x << " ";
    cout << endl;
    return 0;
}
