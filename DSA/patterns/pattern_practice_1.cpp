/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : pattern_practice_1.cpp
 * PROBLEM  : Pattern Practice 1
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Pattern Practice 1
 */
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            cout<< " ";
        }
        int start= i+1;
        for(int j=n-i-1; j<n; j++) {
           
            cout<< start;
            start++;
        }
        for(int j=0; j<i; j++) {
            cout<< start-2;
            start--;
        }
        cout<< "\n";
    }
}
