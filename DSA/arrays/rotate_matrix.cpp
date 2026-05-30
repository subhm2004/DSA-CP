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


/*
 * main()
 * Purpose : Entry point — demo/test for Rotate Matrix
 */
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
