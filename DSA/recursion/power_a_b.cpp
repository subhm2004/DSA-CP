/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : power_a_b.cpp
 * PROBLEM  : Power A B
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

int power(int& a, int b) { // not an optimised approach
    if(b==0) {
        return 1;
    }
   int ans = a* power(a, b-1);
}



/*
 * fastpower()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int& a, int b
 * Returns : int
 */
int fastpower(int& a, int b) {
    if(b==0) {
        return 1;
    }
    if(b%2==0) { // even
        return fastpower(a,b/2) * fastpower(a, b/2);
    }
    else {
        return a* fastpower( a,  b/2) * fastpower(a, b/2);
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Power A B
 */
int main() {
    int a,b;
    cout<< "enter base and exponent"<< endl;
    cin>>a>> b;
    int final= fastpower(a,b);
    cout<< a<< " to the power "<< b<< " is "<< final<< endl;   

}
