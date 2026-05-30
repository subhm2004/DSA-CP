/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : min_element_recursion.cpp
 * PROBLEM  : Min Element Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;



/*
 * minelement()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size, int i, int& min
 * Returns : void
 */
void minelement(int arr[], int size, int i, int& min) {
    if(i>= size) {
        return;
    }
    if(arr[i] < min) {
        min = arr[i];
    }
    minelement(arr, size, i+1, min);

}


/*
 * main()
 * Purpose : Entry point — demo/test for Min Element Recursion
 */
int main() {
    int arr[] = { 23, 34, 45, 56, 12, 67};
    int i=0, size = 6;
    int min = INT_MAX;
    minelement(arr, size, i, min);
    cout<< "minimum element is "<< min << endl;

}
