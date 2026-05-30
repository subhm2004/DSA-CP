/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : inverted_pyramid.cpp
 * PROBLEM  : Inverted Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Inverted Pyramid
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout<< " ";
        }
        for(int j=0; j<n-i; j++) {
            cout<< "* ";
        }
        cout<< "\n";
    }
}
