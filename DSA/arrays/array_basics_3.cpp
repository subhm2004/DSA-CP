/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_3.cpp
 * PROBLEM  : Array Basics 3
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FIND LARGEST ELEMENT — poori array scan karke max nikalo
// ────────────────────────────────────────────────────────────────────────────
// Funda: largest ko arr[0] maan ke har element se compare karo
// Bada mila to largest update — classic linear max scan
// COMPLEX: Time O(n)  |  Space O(n) input ke liye
// ════════════════════════════════════════════════════════════════════════════

// ── main: user input array me largest element dhundho ──────────────────────
//   1) n lo, vector size n se array bharo
//   2) largest = arr[0] se start, har i pe compare
//   3) arr[i] > largest ho to update karo
//   4) final largest print karo
int main() {
    int n;
    cout << "enter the size of array" << endl;
    cin >> n;

    if (n <= 0) {
        cout << "invalid size" << endl;
        return 0;
    }

    vector<int> arr(n);
    cout << "enter the elements of array" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int largest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }

    cout << "largest element is " << largest << endl;
    return 0;
}
