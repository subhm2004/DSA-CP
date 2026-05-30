/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : numeric_pyramid.cpp
 * PROBLEM  : Numeric Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Numeric Pyramid
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout<< j+1;
        }
        cout<< "\n";
    }
}
