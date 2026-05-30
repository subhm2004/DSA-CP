/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : lowercase.cpp
 * PROBLEM  : Lowercase
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * lowercase()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[00]
 * Returns : void
 */
void lowercase(char ch[00]){
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    for(int i=0; i<strlen(ch); i++) {
        ch[i] = ch[i] - 'A' + 'a';
    }
 }


/*
 * main()
 * Purpose : Entry point — demo/test for Lowercase
 */
int main() {
    char ch[100];
    lowercase(ch);
    cout<< ch;
}
