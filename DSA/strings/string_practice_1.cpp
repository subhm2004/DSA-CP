/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : string_practice_1.cpp
 * PROBLEM  : String Practice 1
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
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
    for(int i=0; i< str.length(); i++) {
        if(ans.length() > 0 && str[i] == ans[ans.length()-1]) {
            ans.pop_back();
        }
        else {
            ans.push_back(str[i]);
        }
    }
    cout<< ans<< endl;
}


/*
 * removepart()
 * Purpose : Standard DSA solution for this problem.
 * Returns : void
 */
void removepart() {
    string str = "daabcbaabcbc";
    string target = "abc";
    int i=0;
    while(i < str.length()) {
        if(str.find(target)) {
            str.erase(i,3);
        }
    }
    cout<< str;
}



/*
 * main()
 * Purpose : Entry point — demo/test for String Practice 1
 */
int main() {
    removepart();
}
