/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : numeric_hollow.cpp
 * PROBLEM  : Numeric Hollow
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Numeric Hollow
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            cout<< " ";
        }
        for(int j=0; j< 2*i+1; j++) {
            if(j==0) {
                cout<< j+1;
            }
            else if(j== 2*i) {
                cout<< i+1;
            }
            else {
                cout<< " ";
            }
        }
        cout<< "\n";
    }
    for(int m=1; m<=n; m++) {
        cout<< m<< " ";
    }

}
