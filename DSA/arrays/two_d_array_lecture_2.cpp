/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : two_d_array_lecture_2.cpp
 * PROBLEM  : Two D Array Lecture 2
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : Time: O(n*m)  |  Space: O(1) or O(n*m)
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D ARRAY OPERATIONS — column sum, search, min/max
// ────────────────────────────────────────────────────────────────────────────
// Funda: nested loops se 2D matrix traverse — row-wise ya column-wise
// columnsum: har column ka total, linearsearch: element dhundho
// maxelement/minelement: poori matrix scan
// COMPLEX: Time O(n*m) per operation  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── columnsum: har column ke elements ka sum ───────────────────────────────
//   1) outer loop columns (i), inner loop rows (j)
//   2) arr[j][i] add karo — column-wise sum
//   3) har column ka total print
void columnsum(int arr[3][3]) {
    for(int i=0; i<3; i++) {
        int sum =0;
        for(int j=0; j<3; j++) {
            sum = sum + arr[j][i];
        }
        cout<< "sum of "<< i+1 << "column elements are "<< sum<< endl;
    }
}


// ── linearsearch: 2D matrix me element dhundho ─────────────────────────────
//   1) nested loop — har cell check
//   2) match mila to row, column print + flag=1
//   3) flag==0 to not found
void linearsearch(int arr[3][3], int search) {
    int flag =0;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(arr[i][j]== search) {
                cout<< "element found at row "<< i<< "and column "<< j<< endl;
                flag=1;
                break;
            }
        }
    }
    if(flag==0) {
        cout<< "element not found"<< endl;
    }
}


// ── maxelement: matrix ka maximum element ───────────────────────────────────
//   1) max = INT_MIN se start
//   2) har cell pe compare — bada mila to update
//   3) max return
int maxelement(int arr[3][3]) {
    int max = INT_MIN;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(arr[i][j]> max) {
                max = arr[i][j];
            }
        }
    }
    return max;
}


// ── minelement: matrix ka minimum element ───────────────────────────────────
//   1) min = INT_MAX se start
//   2) har cell pe compare — chhota mila to update
//   3) min return
int minelement(int arr[3][3]) {
    int min = INT_MAX;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(arr[i][j] < min) {
                min = arr[i][j];
                
            }
        }
    }
    return min;
}


// ── main: 2D array input, min/max print ────────────────────────────────────
//   1) 3x3 matrix user input
//   2) print matrix
//   3) maxelement aur minelement call
int main() {
    int search;
    int arr[3][3];
    
    cout<< "enter the elements of array"<< endl;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cin>> arr[i][j];
        }
    }
    cout<< "elements of array are "<< endl;
    for(int i=0; i<3 ; i++) {
        for(int j=0; j<3; j++) {
            cout << arr[i][j]<< " ";

        }
        cout<< "\n";
    }
   
   
   
   int maximum = maxelement(arr);
   cout<< "maximum element of array is "<< maximum << endl;
   int minimum = minelement(arr); 
   cout<< "minimum elemnet of array is "<< minimum<< endl;  
    return 0;
}
