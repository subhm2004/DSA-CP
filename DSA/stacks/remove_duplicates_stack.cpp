/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : remove_duplicates_stack.cpp
 * PROBLEM  : Remove Duplicates Stack
 * LEETCODE : 1047 — Remove All Adjacent Duplicates In String
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;


/*
 * reversestack()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : stack<char>&st
 * Returns : void
 */
void reversestack(stack<char>&st){
    stack<char>sp;
    while(!st.empty()){
        // Opening bracket — push onto stack
        sp.push(st.top());
        st.pop();
    }
    while(!sp.empty()){
        cout<< sp.top();
        // Matching bracket — pop from stack
        sp.pop();
    }
}


/*
 * removeduplicates()
 * Purpose : Hash set or sorting to find duplicates.
 * Params  : string& str, stack<char>&st
 * Returns : void
 */
void removeduplicates(string& str, stack<char>&st){
    int i=0;
    st.push(str[i]);
    i++;
    while(i<str.length()){
        if(!st.empty() && str[i]== st.top()){
            st.pop();
        }
        else {
            st.push(str[i]);
        }
        i++;    
    }
    reversestack(st); 
       
}


/*
 * main()
 * Purpose : Entry point — demo/test for Remove Duplicates Stack
 */
int main(){
    string str = "azxxzy";
    stack<char>st;
    removeduplicates(str,st);

}
