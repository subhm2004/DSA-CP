/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : permutations_of_string.cpp
 * PROBLEM  : Permutations Of String
 * LEETCODE : 46 — Permutations
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Fix one char; recurse on remaining positions.
 * COMPLEX  : Time: O(n!)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * permutations()
 * Purpose : Fix one char; recurse on remaining positions.
 * Params  : string &str, int index
 * Returns : void
 */
void permutations(string &str, int index){
    if(index>= str.length()){
        cout<< str << endl;
        return;
    }
    for(int j=index; j<str.length();j++){
        swap(str[index],str[j]);
        permutations(str,index+1);
        swap(str[index],str[j]); // in the end original string return
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Permutations Of String
 */
int main(){
    string str= "abcd";
    int index= 0;
    permutations(str,index);
}
