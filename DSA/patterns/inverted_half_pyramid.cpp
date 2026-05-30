/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : inverted_half_pyramid.cpp
 * PROBLEM  : Inverted Half Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Inverted Half Pyramid
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            cout<< "*";
        }
        cout<< "\n";
    }
}
