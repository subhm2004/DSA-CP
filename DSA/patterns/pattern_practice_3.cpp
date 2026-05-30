/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : pattern_practice_3.cpp
 * PROBLEM  : Pattern Practice 3
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Pattern Practice 3
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout<< i+j+1;
        }
        cout<< "\n";
    }

}
