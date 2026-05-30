/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : string_elements_recursion.cpp
 * PROBLEM  : String Elements Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * findelement()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : string str, int size, int i, char target
 * Returns : void
 */
void findelement(string str, int size, int i, char target) {
    if(i>= size) {
        return;
    }
    if(str[i] == target) {
        cout<< "target found at index "<< i<< endl;
    }
    findelement(str, size, i+1, target);
}


/*
 * main()
 * Purpose : Entry point — demo/test for String Elements Recursion
 */
int main() {
    string str = "vanshika";
    int size = str.length();
    int i=0;
    char target = 'a';
    findelement(str, size, i, target);
    return 0;
}
