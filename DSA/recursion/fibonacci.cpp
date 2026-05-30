/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : fibonacci.cpp
 * PROBLEM  : Fibonacci
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + recursive call on smaller input.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * fibonacci()
 * Purpose : Base case + recursive call on smaller input.
 * Params  : int n
 * Returns : int
 */
int fibonacci(int n) {
    // Base case: n == 1
    if(n==1) {
        return 0;
    }
    if(n==2) {
        return 1;
    }
    int fib = fibonacci(n-1) + fibonacci(n-2);
    return fib;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Fibonacci
 */
int main() {
    int n;
    cout<< "enter number of last term of fibonacci series"<< endl;
    cin>> n;
    int ans = fibonacci(n);
    cout<< n<< " term of series is "<<ans<< endl;
    return 0;
}
