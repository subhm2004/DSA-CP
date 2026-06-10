/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : transpose_matrix.cpp
 * PROBLEM  : Transpose Matrix
 * LEETCODE : 867 — Transpose Matrix
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Rotate/transpose matrix in-place or with extra space.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TRANSPOSE MATRIX — rows aur columns swap
// ────────────────────────────────────────────────────────────────────────────
// Funda: transpose me arr[i][j] -> output[j][i]
// Print karte waqt arr[j][i] access karo — rows columns ban jate hain
// COMPLEX: Time O(n*m)  |  Space O(1) if print only
// ════════════════════════════════════════════════════════════════════════════

// ── main: 3x3 matrix transpose print karo ──────────────────────────────────
//   1) arr[3][3] declare
//   2) print loop me arr[j][i] — column i, row j
//   3) original matrix bhi print for comparison
int main() {
    int arr[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout<<  arr[j][i];  // transpose: row-col swap
        }
        cout<< endl;
    }
    cout<< "new matrix is "<< endl;
    for(int i=0; i< 3; i++) {
        for(int j=0; j<3; j++) {
            cout<< arr[i][j]<<  " ";
        }
        cout<< endl;
    }
}
