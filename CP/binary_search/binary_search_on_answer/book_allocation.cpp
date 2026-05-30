/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : book_allocation.cpp
 * PROBLEM  : Allocate books to M students — minimize max pages
 * APPROACH : BS on answer (max pages), greedy check
 * COMPLEX  : Time: O(n log(sum))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool canAllocate(const vector<int> &pages, int students, int maxPages) {
    int count = 1, curr = 0;
    for (int p : pages) {
        if (p > maxPages)
            return false;
        if (curr + p <= maxPages)
            curr += p;
        else {
            count++;
            curr = p;
        }
    }
    return count <= students;
}

int minMaxPages(const vector<int> &pages, int students) {
    if ((int)students > (int)pages.size())
        return -1;

    int lo = *max_element(pages.begin(), pages.end());
    int hi = accumulate(pages.begin(), pages.end(), 0);
    int ans = hi;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canAllocate(pages, students, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> pages = {12, 34, 67, 90};
    int students = 2;
    cout << "Minimum max pages = " << minMaxPages(pages, students) << endl;
    return 0;
}
