/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : two_dimensional_array.cpp
 * PROBLEM  : Two Dimensional Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D ARRAY BASICS — input, print, row-wise sum
// ────────────────────────────────────────────────────────────────────────────
// Funda: row x col matrix — nested loops se input/output
// Har row ka sum alag calculate — prefix sum per row
// COMPLEX: Time O(n*m)  |  Space O(1) extra
// ════════════════════════════════════════════════════════════════════════════

// ── main: 2D array input, print, row sums ────────────────────────────────────
//   1) row, col input — matrix bharo
//   2) nested loop se matrix print (tab-separated)
//   3) har row i ka sum calculate karke print
int main() {
    int row, col;
    cout<< "enter the number of rows and columns"<< endl;
    cin>> row>> col;
    int arr[20][20];
    cout<< "enter the elements of array"<< endl;
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            cin>> arr[i][j];
        }
    }
    cout<< "2-D array is"<< endl;
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            cout<< arr[i][j]<< "\t";
        }
        cout<< "\n";
    }
    for(int i=0; i<row; i++) {
        int sum=0;
        for(int j=0; j<col; j++) {
            sum = sum + arr[i][j];

        }
        cout<< "sum of elements of row "<< i<< "is "<< sum<< endl;
    }
    return 0;
}
