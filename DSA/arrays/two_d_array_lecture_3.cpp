/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : two_d_array_lecture_3.cpp
 * PROBLEM  : Two D Array Lecture 3
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * transpose()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[3][3]
 * Returns : void
 */
void transpose(int arr[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << arr[j][i] << " ";
        }
        cout<< endl;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Two D Array Lecture 3
 */
int main() {
    int arr[3][3];
    cout<< "enter the elements of array"<< endl;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cin>> arr[i][j];
        }
    }
    cout<< "elements of array are\n";
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout<< arr[i][j]<< " ";
        }
        cout<< endl;
    }
    cout<< "transpose of the matrix is "<<endl;
    transpose(arr);
    return 0;
}
