/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : palindrome_string.cpp
 * PROBLEM  : Palindrome String
 * LEETCODE : 125 — Valid Palindrome
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * checkpallindrome()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : string& str, int i, int j
 * Returns : bool
 */
bool checkpallindrome(string& str, int i, int j) {
    if(i>j) {
        return true;
    }
    if(str[i]== str[j]) {
        checkpallindrome(str, i+1, j-1);
    }
    else {
        return false;
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Palindrome String
 */
int main() {
    string str = "aman";
    int i=0, j= str.length() -1;
    bool ans = checkpallindrome(str, i, j);
    cout<< ans<< endl;

}
