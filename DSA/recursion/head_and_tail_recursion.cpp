/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : head_and_tail_recursion.cpp
 * PROBLEM  : Head And Tail Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * counting()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n
 * Returns : void
 */
void counting(int n) {
    // Base case: n == 0
    if(n==0) {
        return ;
    }
    cout<< n<< " ";
    counting(n-1);
}


/*
 * counting2()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int n
 * Returns : void
 */
void counting2(int n) {
    // Base case: n == 0
    if(n==0){
        return;
    }
    counting2(n-1);
    cout<< n<< " ";
}


/*
 * main()
 * Purpose : Entry point — demo/test for Head And Tail Recursion
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    counting(n);
    cout<< endl;
    counting2(n);
}
