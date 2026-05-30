/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : factorial.cpp
 * PROBLEM  : Factorial
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + recursive call on smaller input.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * factorial()
 * Purpose : Base case + recursive call on smaller input.
 * Params  : int n
 * Returns : int
 */
int factorial(int n) {
    if(n==0 || n==1) {
        return 1;
    }
    int fact = n* factorial(n-1);
    return fact;
}


/*
 * counting()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n
 * Returns : void
 */
void counting(int n) {
    // Base case: n == 0
    if(n==0) {
        return;
    }
    cout<< n<< " ";
    counting(n-1);


}


/*
 * main()
 * Purpose : Entry point — demo/test for Factorial
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    counting(n);
    return 0;
}
