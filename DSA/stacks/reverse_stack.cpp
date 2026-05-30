/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : reverse_stack.cpp
 * PROBLEM  : Reverse Stack
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;



/*
 * insertatbottom()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int> &sp, int &temp, int &element
 * Returns : void
 */
void insertatbottom(stack<int> &sp, int &temp, int &element){
    if(sp.empty()){
        // Opening bracket — push onto stack
        sp.push(element);
        return;
    }
    // Matching bracket — pop from stack
    sp.pop();
    insertatbottom(sp,sp.top(),element);
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * reversestack()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : stack<int> &sp, int &temp, int& element
 * Returns : void
 */
void reversestack(stack<int> &sp, int &temp, int& element){
    if(sp.empty()){
        return;
    }
    // Matching bracket — pop from stack
    sp.pop();
    reversestack(sp,sp.top(), element);
    insertatbottom(sp,temp,temp);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Reverse Stack
 */
int main(){
    stack<int> sp;
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
    int temp= sp.top();
    int element= sp.top();
    reversestack(sp,temp,element);
    while(!sp.empty()){
        cout<< sp.top()<< endl;
        // Matching bracket — pop from stack
        sp.pop();
    }
}
