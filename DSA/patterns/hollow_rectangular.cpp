/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : hollow_rectangular.cpp
 * PROBLEM  : Hollow Rectangular
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Hollow Rectangular
 */
int main() {
    int m,n;
    cout<< "enter row and column number"<< endl;
    cin>>m>> n;
    for(int i=0; i<m; i++) {
        if(i==0 || i==m-1) {
            for(int j=0; j<n; j++ ) {
                cout<< "* ";
            }
        }
        else { cout<< "* ";
            for(int j=1; j<=n-2; j++) {
                cout<< "  ";
            }
            cout<< "* ";
        }
        cout<< "\n";

    }
}
