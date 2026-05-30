/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : container_with_most_water.cpp
 * PROBLEM  : Max area between two vertical lines
 * APPROACH : Move pointer at shorter height inward
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxArea(vector<int> h) {
    int l = 0, r = (int)h.size() - 1, best = 0;

    while (l < r) {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r])
            l++;
        else
            r--;
    }
    return best;
}

int main() {
    vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max water area = " << maxArea(h) << endl;
    return 0;
}
