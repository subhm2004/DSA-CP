/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : radix_sort.cpp
 * PROBLEM  : Radix Sort (non-negative integers)
 * APPROACH : Stable counting sort on each digit (LSD)
 * COMPLEX  : Time: O(d * (n + 10))  |  Space: O(n + 10)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RADIX SORT — Digit-by-digit LSD counting sort
// ────────────────────────────────────────────────────────────────────────────
// Har digit position (1s, 10s, 100s...) pe stable counting sort
// d passes — d = number of digits in max element
// Non-comparison sort — integers ke liye efficient
// ════════════════════════════════════════════════════════════════════════════

// ── countingSortByDigit: ek digit position pe counting sort ───────────────────
//   1) exp = 1, 10, 100... — current digit place
//   2) (x/exp)%10 se digit nikalo
//   3) stable counting sort on that digit
void countingSortByDigit(vector<int> &a, int exp) {
    int n = a.size();
    vector<int> output(n), count(10, 0);

    for (int x : a)
        count[(x / exp) % 10]++;  // digit frequency

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }
    a = output;
}

// ── radixSort: har digit pe counting sort ───────────────────────────────────
//   1) max element ke digits count
//   2) exp = 1, 10, 100... jab tak max/exp > 0
void radixSort(vector<int> &a) {
    if (a.empty())
        return;

    int maxVal = *max_element(a.begin(), a.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(a, exp);  // LSD pass
}

// ── main: radix sort demo ───────────────────────────────────────────────────
int main() {
    vector<int> a = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(a);
    for (int x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
