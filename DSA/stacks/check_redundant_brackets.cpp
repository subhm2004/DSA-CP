/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : check_redundant_brackets.cpp
 * PROBLEM  : Check Redundant Brackets
 * LEETCODE : 678 — Valid Parenthesis String
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * redundantbracket()
 * Purpose : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * Params  : string &str, stack<char>&sp
 * Returns : bool
 */
bool redundantbracket(string &str, stack<char>&sp){
    int count=0;
    int index=0;
    while(index < str.length()){
        if(str[index]== '(' || str[index]== '+' || str[index]== '*' || str[index]== '-' || str[index]== '/'){
            // Opening bracket — push onto stack
            sp.push(str[index]);
        }
        if(str[index]== ')'){
            count=0;
            while(!sp.empty() && sp.top() != '(') {
                if(sp.top()== '+' || sp.top()== '*' || sp.top()== '-' || sp.top()== '/'){
                count++;
                // Matching bracket — pop from stack
                sp.pop();
                }
            }
            if(count == 0){
                return true;
            }
            
            // Matching bracket — pop from stack
            sp.pop();
        }
        index++;
    }
    if(count!= 0){
        return false;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Check Redundant Brackets
 */
int main(){
    string str= "((a+b)*((c)+d))";
    stack<char>sp;
    bool ans= redundantbracket(str,sp);
    cout<< ans<< endl;
}
