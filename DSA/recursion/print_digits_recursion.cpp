/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : print_digits_recursion.cpp
 * PROBLEM  : Print Digits Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * printdigit()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n
 * Returns : void
 */
void printdigit(int n) {
    // Base case: n == 0
    if(n==0) {
        return ;
    }
     int a = n/10;
    printdigit(a);
    int rem = n%10;
    cout<< "digit" << rem<< endl;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Print Digits Recursion
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    printdigit(n);    
}
