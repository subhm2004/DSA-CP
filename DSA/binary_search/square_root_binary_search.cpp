/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : square_root_binary_search.cpp
 * PROBLEM  : Square Root Binary Search
 * LEETCODE : 69 — Sqrt(x)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * sqrt()
 * Purpose : Binary search — eliminate half the search space each step.
 * Params  : int n, int s, int e
 * Returns : int
 */
int sqrt(int n, int s, int e) {
    int ans = -1;
    int mid = s + (e - s) / 2;
    while (s <= e) {
        if (mid * mid == n) {
            return mid;
        } else if (mid * mid > n) {
            e = mid - 1;
        } else {
            ans = mid;
            s = mid + 1;
        }
        mid = s + (e - s) / 2;
    }
    return ans;
}



/*
 * sqrtWithPrecision()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int n, int precision
 * Returns : double
 */
double sqrtWithPrecision(int n, int precision) {
    int s = 0, e = n;
    int intPart = sqrt(n, s, e);

    double ans = intPart;
    double increment = 0.1;
    for (int i = 0; i < precision; i++) {
        while (ans * ans <= n) {
            ans += increment;
        }
        ans -= increment;
        increment /= 10;
    }

    return ans;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Square Root Binary Search
 */
int main() {
    int n;
    cout << "Enter any number: ";
    cin >> n;

    int precision;
    cout << "Enter the number of decimal places for precision: ";
    cin >> precision;

    double ans = sqrtWithPrecision(n, precision);
    cout << "Square root of " << n << " is: " << ans << endl;

    return 0;
}
