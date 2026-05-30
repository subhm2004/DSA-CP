/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : valid_parentheses.cpp
 * PROBLEM  : Valid Parentheses
 * LEETCODE : 20 — Valid Parentheses
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * checkparenthesis()
 * Purpose : Backtrack valid '(' ')' strings.
 * Params  : string& str
 * Returns : bool
 */
bool checkparenthesis(string& str){
    int i=0;
    stack<char>sp;
    while(i< str.length()){
        if(str[i]== '('|| str[i]== '['|| str[i]== '{'){
            // Opening bracket — push onto stack
            sp.push(str[i]);
        }
        else if(str[i]== ')'){
            if(sp.top()== '(' && !sp.empty()){
                // Matching bracket — pop from stack
                sp.pop();
            }
            else {
                return false;
            }
        }
        else if(str[i]== '}' && !sp.empty()){
            if(sp.top()== '{'){
                // Matching bracket — pop from stack
                sp.pop();
            }
            else {
                return false;
            }
        }
        else if(str[i]== ']' && !sp.empty()){
            if(sp.top()== '['){
                // Matching bracket — pop from stack
                sp.pop();
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
        i++;

    }
    if(sp.empty()){
        return true;
    }
    else {
        return false;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Valid Parentheses
 */
int main(){
    string str= "[{()}]";
    int n= str.length();
    bool ans= checkparenthesis(str);
    cout<< ans<< endl;
}
