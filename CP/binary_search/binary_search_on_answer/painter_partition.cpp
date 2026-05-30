/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : painter_partition.cpp
 * PROBLEM  : K painters, boards with lengths — minimize max time
 * APPROACH : BS on answer (max time per painter), greedy partition
 * COMPLEX  : Time: O(n log(sum))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool canPaint(const vector<int> &boards, int k, int maxTime) {
    int painters = 1, curr = 0;
    for (int b : boards) {
        if (b > maxTime)
            return false;
        if (curr + b <= maxTime)
            curr += b;
        else {
            painters++;
            curr = b;
        }
    }
    return painters <= k;
}

int minPaintTime(const vector<int> &boards, int k) {
    int lo = *max_element(boards.begin(), boards.end());
    int hi = accumulate(boards.begin(), boards.end(), 0);
    int ans = hi;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canPaint(boards, k, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> boards = {5, 10, 30, 20, 15};
    int k = 3;
    cout << "Minimum paint time = " << minPaintTime(boards, k) << endl;
    return 0;
}
