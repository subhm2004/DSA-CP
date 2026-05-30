/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : print_sum_recursion.cpp
 * PROBLEM  : Print Sum Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * sumarray()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int& size, int i, int& sum
 * Returns : int
 */
int sumarray(int arr[], int& size, int i, int& sum) {
    if(i>= size) {
        return sum;
    }
    sum = sum + arr[i];
    sumarray(arr, size, i+1, sum);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Print Sum Recursion
 */
int main() {
    int arr[] = {1,2,3,4,5,6} ;
    int size= 6;
    int i=0;
    int sum =0;
    int ans = sumarray(arr, size, i, sum);
    cout<< "sum of array elements are "<< ans<< endl;
}
