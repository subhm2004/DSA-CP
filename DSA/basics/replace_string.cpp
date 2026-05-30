/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : replace_string.cpp
 * PROBLEM  : Replace String
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * replace_space()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[100]
 * Returns : void
 */
void replace_space(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    int i=0;
    while(ch[i] != '\0') {
        if(ch[i] == ' ') {
            ch[i] = '@';
        }
        i++;
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Replace String
 */
int main() {
    char ch[100];
    cout<< ch;
    
}
