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


/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int row, int col
 * Returns : void
 */
void printarray(int arr[][3], int row, int col) {
    for(int j=0; j<col; j++) {
        for(int i=0; i<row; i++) {
            cout<< arr[i][j]<< endl;
        }
    }
}


/*
 * linearsearch()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int& row, int& col, int& target
 * Returns : bool
 */
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


/*
 * maxelement()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int& row, int& col, int& max
 * Returns : int
 */
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


/*
 * rowwisesum()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int& row, int& col
 * Returns : void
 */
void rowwisesum(int arr[][3], int& row, int& col) {   
    for(int i=0; i<row; i++) {
        int sum =0;
        for(int j=0; j< col; j++) {
            sum = sum + arr[i][j];
        }
        cout<< " sum of " << i << " row is " << sum << endl;
    }
}


/*
 * colwisesum()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int& row, int& col
 * Returns : void
 */
void colwisesum(int arr[][3], int& row, int& col) {
    for(int j=0; j<col; j++) {
        int sum =0;
        for(int i=0; i<row; i++) {
            sum = sum + arr[i][j];
        }
        cout<< "sum of "<< j<< " column is "<< sum<< endl;
    }
}


/*
 * diagonalsum()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int& row, int& col
 * Returns : void
 */
void diagonalsum(int arr[][3], int& row, int& col) {
    int sum =0;
    for(int i=0; i< row; i++) {
        sum = sum + arr[i][i];
    }
    cout<< " sum of diagonal elements is "<< sum<< endl;
}


/*
 * printmatrix()
 * Purpose : Rotate/transpose matrix in-place or with extra space.
 * Params  : int arr[][3], int row, int col
 * Returns : void
 */
void printmatrix(int arr[][3], int row, int col) {
    cout<< "matrix is "<< endl;
    for(int i=0; i<row; i++) {
        for(int j=0; j< col; j++) {
            cout<< arr[i][j]<< "  ";
        }
        cout<< endl;
    }
}


/*
 * transpose()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[][3], int row, int col
 * Returns : void
 */
void transpose(int arr[][3], int row, int col) {
    cout<< " transpose of the matrix is "<< endl;
    for(int i=0 ; i< row; i++) {
        for(int j=0 ; j< col; j++) {
            cout<< arr[j][i]<< "  ";
        }
        cout<< endl;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Array Questions
 */
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
