/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : binary_search_on_answer_template.cpp
 * PROBLEM  : Generic template — find min/max X such that isPossible(X)
 * APPROACH : Binary search on answer range [lo, hi]
 * COMPLEX  : Time: O(log(range) * check(X))  |  Space: O(1)
 * ============================================================================
 *
 * Pattern:
 *   1. Identify monotonic predicate isPossible(mid)
 *   2. lo = minimum possible answer, hi = maximum possible answer
 *   3. For MIN answer: if possible → ans=mid, hi=mid-1 else lo=mid+1
 *   4. For MAX answer: if possible → ans=mid, lo=mid+1 else hi=mid-1
 */

#include <bits/stdc++.h>
using namespace std;

bool isPossible(int mid) {
    // Replace with problem-specific check
    return mid * mid >= 50;
}

int binarySearchOnAnswerMin(int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(mid)) {
            ans = mid;
            hi = mid - 1; // minimize answer
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int binarySearchOnAnswerMax(int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(mid)) {
            ans = mid;
            lo = mid + 1; // maximize answer
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int main() {
    cout << "Min X with X^2 >= 50: " << binarySearchOnAnswerMin(0, 100) << endl;
    cout << "Max X with X^2 <= 50: " << binarySearchOnAnswerMax(0, 100) << endl;
    return 0;
}
