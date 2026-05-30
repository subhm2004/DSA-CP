/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : linear_search_recursion.cpp
 * PROBLEM  : Linear Search Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * linearsearch()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int i, int& target
 * Returns : void
 */
void linearsearch(int arr[], int& size,int i, int& target) {
    if(arr[i] == target) {
        cout<< "target found at index "<< i<< endl;
        return;
    }
    linearsearch(arr, size, i+1, target);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Linear Search Recursion
 */
int main() {
    int arr[] = {1,34,23,21,45,43};
    int size= 6;
    int target = 21;
    int i=0;
    linearsearch(arr,size,i,target);
}
