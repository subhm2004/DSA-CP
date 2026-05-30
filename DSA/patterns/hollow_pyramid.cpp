/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : hollow_pyramid.cpp
 * PROBLEM  : Hollow Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Hollow Pyramid
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            cout<< " ";
        }
        for(int j=0; j< 2*i+1; j++) {
            if(j==0 || j== 2*i) {
                cout<< "*";
            }
            else {
                cout<< " ";
            }

        }
        cout<< "\n";
    }
}
