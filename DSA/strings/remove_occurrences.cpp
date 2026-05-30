/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : remove_occurrences.cpp
 * PROBLEM  : Remove Occurrences
 * LEETCODE : 1910 — Remove All Occurrences of a Substring
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;


/*
 * removeoccur()
 * Purpose : Standard DSA solution for this problem.
 * Returns : string
 */
string removeoccur() {
    string str = "daabcbaabcbc";
    string part = "abc";
    int pos = str.find(part);
    while(pos != string::npos) {
        str.erase(pos, part.length());
        pos = str.find(part);
    }
    return str;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Remove Occurrences
 */
int main() {
   string ans= removeoccur();
   cout<< ans<< endl;

}
