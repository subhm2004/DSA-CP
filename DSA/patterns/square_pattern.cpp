/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : square_pattern.cpp
 * PROBLEM  : Square Pattern
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Square Pattern
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
           cout<< "*"; 
        }
        cout<< "\n";
    }
}
