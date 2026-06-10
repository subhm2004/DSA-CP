/*
 * ============================================================================
 * TOPIC    : Misc
 * FILE     : dynamictwo_d.cpp
 * PROBLEM  : Dynamictwo D
 * ABOUT    : Mixed DSA practice problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DYNAMIC 2D ARRAY — heap pe row×col matrix allocate
// ────────────────────────────────────────────────────────────────────────────
// int** arr = array of row pointers
// Har row: new int[col] — alag heap block
// Print: nested loops se values (default 0)
// Cleanup: pehle har row delete[], phir arr delete[]
// ════════════════════════════════════════════════════════════════════════════

// ── main: dynamic 2D array create, print, free ────────────────────────────
//   1) row=5, col=3 set karo
//   2) arr = new int*[row] — row pointers array
//   3) har i: arr[i] = new int[col] — har row allocate
//   4) nested loop se print, phir har row + main array delete
int main(){
    int row= 5;
    int col=3;
    int **arr= new int*[5];
    for(int i=0; i< row; i++){
        arr[i] = new int[col];
    }
    cout<< "2-D array is\n";
    for(int i=0; i< row; i++){
        for(int j=0; j< col; j++){
            cout<< arr[i][j]<< " ";
        }
        cout<< endl;
    }
    for(int i=0; i< row; i++){
        delete []arr[i];
    }
    delete []arr;
}
