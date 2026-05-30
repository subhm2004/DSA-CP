/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : uppercase.cpp
 * PROBLEM  : Uppercase
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * uppercase()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[100]
 * Returns : void
 */
void uppercase(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    for(int i=0; i<strlen(ch); i++) {
        ch[i]= ch[i]-'a'+'A';
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Uppercase
 */
int main() {
    char ch[100];
    uppercase(ch);
    cout<< ch;

}
