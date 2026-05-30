/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : print_extremes.cpp
 * PROBLEM  : Print Extremes
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Print Extremes
 */
int main() {
    int arr[] = {10, 20 ,30, 40, 50, 60, 70, 80};
    int size = 8;
    int i = 0, j = size -1;
    while(i <= j) {
        if( i == j) {
            cout<< arr[i]<< " ";
        }
        else {
        cout<< arr[i]<< " ";
        cout<< arr[j]<< " ";
        }
        i++;
        j--;
        
    }
    return 0;
}
