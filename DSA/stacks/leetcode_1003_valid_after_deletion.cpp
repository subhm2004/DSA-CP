/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : leetcode_1003_valid_after_deletion.cpp
 * PROBLEM  : Leetcode 1003 Valid After Deletion
 * LEETCODE : 1003 — Check If String Is Deletable
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;


/*
 * validstr()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : string str, string& substr
 * Returns : bool
 */
bool validstr(string str, string& substr){
    while(!str.empty()){
        if(str.find(substr)== string::npos){
            return false;
        }
        else {
            int index= str.find(substr);
            str.erase(index,3);
        }
    }
    if(str.empty()){
        return true;
    }
    else {
        return false;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Leetcode 1003 Valid After Deletion
 */
int main(){
    string str= "ababcc";
    string substr= "abc";
    bool ans= validstr(str,substr);
    cout<< ans<< endl;
    
}
