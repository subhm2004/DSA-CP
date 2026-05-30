/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : palindrome_string.cpp
 * PROBLEM  : Palindrome String
 * LEETCODE : 125 — Valid Palindrome
 * ABOUT    : String manipulation with STL
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;


/*
 * pallindrome()
 * Purpose : Standard DSA solution for this problem.
 * Returns : bool
 */
bool pallindrome() {
    string str = "abca";
    int i=0;
    int j= str.length() - 1;
    while(i<j) {
        if(str[i] == str[j]) {
            i++;
            j--;
        }
        else if(str[i] != str[j]){
            str.pop_back();   
        }
    }
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Palindrome String
 */
int main() {
    bool ans = pallindrome();
    cout<< ans<< endl;
}
