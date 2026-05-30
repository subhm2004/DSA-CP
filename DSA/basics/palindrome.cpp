/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : palindrome.cpp
 * PROBLEM  : Palindrome
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * pallindrome()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[100]
 * Returns : bool
 */
bool pallindrome(char ch[100]) {
    cout<< "enter any string"<< endl;
    cin.getline(ch,100);
    int i=0, j= strlen(ch)-1;
    bool same= false;
    while(i<=j) {
        if(ch[i] == ch[j]) {
            same= true;
        }
        else {
            same = false;
            break;
        }
        i++;
        j--;
    }
    return same;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Palindrome
 */
int main() {
    char ch[100];
    bool ans = pallindrome(ch);
    cout<< ans<< endl;
}
