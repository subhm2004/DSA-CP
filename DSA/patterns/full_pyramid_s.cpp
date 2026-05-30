/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : full_pyramid_s.cpp
 * PROBLEM  : Full Pyramid S
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Full Pyramid S
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            cout<< " ";
        }
        for(int j=n-i-1; j<n; j++) {
            cout<< "* ";
        }
        cout<< "\n";
    }
}
