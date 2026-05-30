/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : generate_subsequences.cpp
 * PROBLEM  : Generate Subsequences
 * LEETCODE : 78 — Subsets / Subsequence variant
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Include/exclude each element — recursive branching.
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * subsequence()
 * Purpose : Include/exclude each element — recursive branching.
 * Params  : string str, string ans, int i
 * Returns : void
 */
void subsequence(string str, string ans, int i ) {
    if(i== str.length()) {
        cout<< ans<< " ";
        return;
    }
     subsequence(str, ans, i+1);

    ans.push_back(str[i]);
    subsequence(str, ans, i+1);
    
}


/*
 * subsequence2()
 * Purpose : Include/exclude each element — recursive branching.
 * Params  : string str, string ans, int i
 * Returns : void
 */
void subsequence2(string str, string ans, int i){
    if(i>= str.length()){
        cout<< ans<< endl;
        return;
    }
    char ch= str[i];
    ans.push_back(ch);
    subsequence2(str,ans,i+1);
    ans.pop_back();
    subsequence2(str,ans,i+1);
}



/*
 * main()
 * Purpose : Entry point — demo/test for Generate Subsequences
 */
int main() {
    string str= "abc";
    string ans= "";
    int i=0;
    subsequence2(str,ans, i);

}
