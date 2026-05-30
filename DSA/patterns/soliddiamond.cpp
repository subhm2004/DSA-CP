/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : soliddiamond.cpp
 * PROBLEM  : Soliddiamond
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Soliddiamond
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j< n-1-i; j++) {
            cout<< " ";
        }
        for(int j=n-i-1; j< n; j++) {
            cout<< "* ";
        }
        cout<< "\n";
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout<< " ";
        }
        for(int j=i; j<n; j++) {
            cout<< "* ";
        }
        cout<< "\n";
    }
}
