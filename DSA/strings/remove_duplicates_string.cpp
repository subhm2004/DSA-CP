/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : remove_duplicates_string.cpp
 * PROBLEM  : Remove Duplicates String
 * LEETCODE : 1047 — Remove All Adjacent Duplicates In String
 * ABOUT    : String manipulation with STL
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;


/*
 * duplicate()
 * Purpose : Hash set or sorting to find duplicates.
 * Returns : void
 */
void duplicate() {
    string str = "abbaca";
    string ans = "";
    int i=0;
    while(i< str.length()) {
        if(ans.length() >0) {
            if(str[i] != ans[ans.length()-1]) {
               ans.push_back(str[i]);
            }
            else {
               ans.pop_back();
            }
        }
        else {
            ans.push_back(str[i]);
        }
        i++;
    }    
    cout<< ans;       
}


/*
 * main()
 * Purpose : Entry point — demo/test for Remove Duplicates String
 */
int main() {
    duplicate();
}
