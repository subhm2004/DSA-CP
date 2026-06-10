/*
 * ============================================================================
 * TOPIC    : Misc
 * FILE     : array_questions.cpp
 * PROBLEM  : Array Questions
 * ABOUT    : Mixed DSA practice problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D ARRAY QUESTIONS — print, search, sum, transpose
// ────────────────────────────────────────────────────────────────────────────
// Fixed 3x3 matrix pe common operations practice
// Column-wise print, linear search, max element
// Row/column sum, diagonal sum, matrix print
// Transpose: rows ko columns mein convert
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: column-by-column print karo ───────────────────────────────
//   1) outer loop col (j), inner loop row (i)
//   2) har column ke elements vertically print
//   3) arr[i][j] cout — column order mein output
void printarray(int arr[][3], int row, int col) {
    for(int j=0; j<col; j++) {
        for(int i=0; i<row; i++) {
            cout<< arr[i][j]<< endl;
        }
    }
}

// ── linearsearch: 2D array mein target dhundho ────────────────────────────
//   1) har row i pe loop
//   2) har column j pe check arr[i][j] == target
//   3) match mila -> true return
//   4) poora scan fail -> false
bool linearsearch(int arr[][3], int& row, int& col, int& target) {
    for(int i=0; i<row; i++){
        for(int j=0; j< col; j++) {
            if(arr[i][j] == target) {
                return true;
            }
        }
    }
    return false;
}

// ── maxelement: matrix ka maximum element nikalo ──────────────────────────
//   1) max se compare karte hue har cell scan
//   2) arr[i][j] > max ho to max update
//   3) poora matrix traverse
//   4) final max return
int maxelement(int arr[][3], int& row, int& col, int& max) {
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            if(arr[i][j] > max) {
                max = arr[i][j];
            }
        }
    }
    return max;
}

// ── rowwisesum: har row ka sum print karo ─────────────────────────────────
//   1) har row i ke liye sum = 0
//   2) us row ke sab columns j add karo
//   3) row i ka sum print
//   4) next row
void rowwisesum(int arr[][3], int& row, int& col) {   
    for(int i=0; i<row; i++) {
        int sum =0;
        for(int j=0; j< col; j++) {
            sum = sum + arr[i][j];
        }
        cout<< " sum of " << i << " row is " << sum << endl;
    }
}

// ── colwisesum: har column ka sum print karo ──────────────────────────────
//   1) har column j ke liye sum = 0
//   2) us column ke sab rows i add karo
//   3) column j ka sum print
//   4) next column
void colwisesum(int arr[][3], int& row, int& col) {
    for(int j=0; j<col; j++) {
        int sum =0;
        for(int i=0; i<row; i++) {
            sum = sum + arr[i][j];
        }
        cout<< "sum of "<< j<< " column is "<< sum<< endl;
    }
}

// ── diagonalsum: main diagonal (top-left to bottom-right) ka sum ──────────
//   1) sum = 0 initialize
//   2) i=0 se row-1: arr[i][i] add (same row-col index)
//   3) total diagonal sum print
void diagonalsum(int arr[][3], int& row, int& col) {
    int sum =0;
    for(int i=0; i< row; i++) {
        sum = sum + arr[i][i];
    }
    cout<< " sum of diagonal elements is "<< sum<< endl;
}

// ── printmatrix: matrix ko row-wise print karo ────────────────────────────
//   1) "matrix is" header print
//   2) har row i, har col j — arr[i][j] space-separated
//   3) har row ke baad newline
void printmatrix(int arr[][3], int row, int col) {
    cout<< "matrix is "<< endl;
    for(int i=0; i<row; i++) {
        for(int j=0; j< col; j++) {
            cout<< arr[i][j]<< "  ";
        }
        cout<< endl;
    }
}

// ── transpose: matrix ka transpose print (swap rows/cols) ─────────────────
//   1) transpose header print
//   2) i rows, j cols — arr[j][i] print (indices swap)
//   3) har "row" (original column) ke baad newline
void transpose(int arr[][3], int row, int col) {
    cout<< " transpose of the matrix is "<< endl;
    for(int i=0 ; i< row; i++) {
        for(int j=0 ; j< col; j++) {
            cout<< arr[j][i]<< "  ";
        }
        cout<< endl;
    }
}

// ── main: demo — 3x3 array setup ──────────────────────────────────────────
//   1) 3x3 sample matrix declare
//   2) row, col, max variables set
//   3) vector size demo print
int main() {
    int arr[3][3] = {
                     {10,20,30},
                     {40,50,60},
                     {70,80,90}
                    } ;

    int row = 3;
    int col = 3;
    int max = INT_MIN;
    vector<int>brr;
    cout<< brr.size() << endl;
    
}
