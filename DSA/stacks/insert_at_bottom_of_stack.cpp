/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : insert_at_bottom_of_stack.cpp
 * PROBLEM  : Insert At Bottom Of Stack
 * LEETCODE : 225 — Implement Stack using Queues
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * insertatbottom()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int> &sp, stack<int> &st, int& element
 * Returns : void
 */
void insertatbottom(stack<int> &sp, stack<int> &st, int& element){
    while(!sp.empty()){
        st.push(sp.top());
        // Matching bracket — pop from stack
        sp.pop();    
    }
    st.push(element);
    while(!st.empty()){
        // Opening bracket — push onto stack
        sp.push(st.top());
        st.pop();
    }
}


/*
 * insertrec()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int> &sp, int& element, int temp
 * Returns : void
 */
void insertrec(stack<int> &sp, int& element, int temp){
    if(sp.empty()){
        // Opening bracket — push onto stack
        sp.push(element);
        return;
    }
    // Matching bracket — pop from stack
    sp.pop();
    insertrec(sp,element, sp.top());
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Insert At Bottom Of Stack
 */
int main(){
    int element= 5;
    stack<int>sp;
    // Opening bracket — push onto stack
    sp.push(10);
    // Opening bracket — push onto stack
    sp.push(20);
    // Opening bracket — push onto stack
    sp.push(30);
    // Opening bracket — push onto stack
    sp.push(40);
    // Opening bracket — push onto stack
    sp.push(50);
    stack<int>st;
    int temp= sp.top();
    insertatbottom(sp,st,element);
    cout<< "Stack is : "<< endl;
    while(!sp.empty()){
        cout<< sp.top()<< endl;
        // Matching bracket — pop from stack
        sp.pop();
    }
}
