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


/*
 * main()
 * Purpose : Entry point — demo/test for Transpose Matrix
 */
int main() {
    int arr[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout<<  arr[j][i];
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
