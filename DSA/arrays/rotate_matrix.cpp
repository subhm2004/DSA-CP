/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : rotate_matrix.cpp
 * PROBLEM  : Rotate Matrix
 * LEETCODE : 48 — Rotate Image
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Rotate/transpose matrix in-place or with extra space.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ROTATE MATRIX 90° — transpose + reverse rows approach
// ────────────────────────────────────────────────────────────────────────────
// Funda: 90° clockwise = transpose karke har row reverse
// Yahan column-wise copy attempt — arr[i][j] -> c[j][k]
// COMPLEX: Time O(n²)  |  Space O(n²) for output matrix
// ════════════════════════════════════════════════════════════════════════════

// ── main: 3x3 matrix 90° rotate karo ───────────────────────────────────────
//   1) original arr[3][3] declare
//   2) column-wise copy into rotated matrix c
//   3) rotated matrix print karo
int main() {
    int arr[3][3] = {{1,2,3},
                     {4,5,6},
                     {7,8,9}
                    };
    for(int i=0; i<3; i++) {
        int k = 2;
        for(int j=0; j<3; j++) {
            c[j][k] = arr[i][j];
        }
        k--;
    }
    cout<< "new array is\n"<< endl;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout<< c[i][j]<< " ";
        }
        cout<< endl;
    } 
           
}
