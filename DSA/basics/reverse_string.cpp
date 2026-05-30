/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : reverse_string.cpp
 * PROBLEM  : Reverse String
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * reversestring()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : char ch[100]
 * Returns : void
 */
void reversestring(char ch[100]) {
    cout<< "enter any string" << endl;
    cin.getline(ch,100);
    int i=0, j=strlen(ch) -1;
    while(i<=j) {
        swap(ch[i], ch[j]);
        i++;
        j--;
    }
}


/*
 * printstr()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[100]
 * Returns : void
 */
void printstr(char ch[100]) {
    for(int i=0; i<strlen(ch); i++) {
        cout<< ch[i];
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Reverse String
 */
int main() {
    char ch[100];   
    reversestring( ch);
    printstr(ch);

}
