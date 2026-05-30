/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : minimum_bracket_reversals.cpp
 * PROBLEM  : Minimum Bracket Reversals
 * LEETCODE : 1249 — Minimum Remove to Make Valid Parentheses
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Stack: push '(', '[', '{'; pop when closing bracket matches.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;


/*
 * reversalcount()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : string& str
 * Returns : int
 */
int reversalcount(string& str){
    stack<char>st;
        if(str.length()&1){
        return -1; // expression can't me made valid
        }
        else {
            int i=0;
            while(i<str.length()){
                if(str[i]== '{'){
                   st.push(str[i]);
                }
                else {
                  if(st.empty())
                    st.push(str[i]);
                  else {
                    if(st.top()== '{'){
                        st.pop();
                    }
                    else {
                        st.push(str[i]);
                    }
                  }
                }
                i++;
            }
        }
        int op_count=0;
        if(!st.empty()){
            while(!st.empty()){
                int temp= st.top();
                st.pop();
                if((st.top()== '}' && temp== '}') || (st.top()== '{' && temp== '{') ){
                    op_count++;
                    st.pop();
                }
                
                else if(temp== '}' && st.top()== '{' || (temp== '{' && st.top()== '}')){
                    op_count= op_count+2;
                    st.pop();
                }
            } 
            return op_count;  
        }
        else {
            return 0;
        }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Minimum Bracket Reversals
 */
int main(){
    string str= "{}}{{{";
    int ans= reversalcount(str);
    cout<< ans<< endl;
}
