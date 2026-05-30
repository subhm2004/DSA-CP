/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : say_digits.cpp
 * PROBLEM  : Say Digits
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <math.h>
using namespace std;



/*
 * printdigit()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : string arr[10], int& n
 * Returns : void
 */
void printdigit(string arr[10], int& n) {
    // Base case: n == 0
    if(n==0) {
        return;
    }
    int digit = n % 10;
    n= n/10;
    printdigit(arr, n);
    cout<< arr[digit]<< endl;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Say Digits
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    string arr[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    printdigit(arr, n);    
}
