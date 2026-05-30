/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : max_element_recursion.cpp
 * PROBLEM  : Max Element Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;



/*
 * maxelement()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size, int& max, int i
 * Returns : void
 */
void maxelement(int arr[], int size, int& max , int i) { 
    if(i>=size) {
        return;
    }
    
    if(arr[i]> max) {
        max = arr[i];
    }
    maxelement(arr, size , max, i+1);
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Max Element Recursion
 */
int main() {
    int arr[] = { 10,12,34,35,45,67};
    int size = 6;
    int i=0;
    int max = INT_MIN;

    maxelement(arr, size, max, i);
    cout<< "maximum element is "<< max << endl;
    return 0;
}
