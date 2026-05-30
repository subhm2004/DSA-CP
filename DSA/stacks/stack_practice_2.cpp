/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_practice_2.cpp
 * PROBLEM  : Stack Practice 2
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <limits.h>
using namespace std;



/*
 * getmiddle()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int>&sp, int& size, int& mid
 * Returns : void
 */
void getmiddle(stack<int>&sp, int& size, int& mid){
    if(size== mid){
        cout<< sp.top()<< endl;
        return;
    }
    int temp= sp.top();
    // Matching bracket — pop from stack
    sp.pop();
    size--;
    getmiddle(sp,size,mid);
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * insertatbottom()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int>&sp, int &element
 * Returns : void
 */
void insertatbottom(stack<int>&sp, int &element ){
    if(sp.empty()){
        // Opening bracket — push onto stack
        sp.push(element);
        return;
    }
    int temp= sp.top();
    // Matching bracket — pop from stack
    sp.pop();
    insertatbottom(sp,element);
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * reversestack()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : stack<int>&sp
 * Returns : void
 */
void reversestack(stack<int>&sp){
    if(sp.empty()){
        return;
    }
    int temp= sp.top();
    // Matching bracket — pop from stack
    sp.pop();
    reversestack(sp);
    insertatbottom(sp,temp);
}


/*
 * insertinstack()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int>&sp, int& element
 * Returns : void
 */
void insertinstack(stack<int>&sp, int& element){
    if( sp.empty() || sp.top() <element){
        // Opening bracket — push onto stack
        sp.push(element);
        return;
    }
    int temp= sp.top();
    // Matching bracket — pop from stack
    sp.pop();
    insertinstack(sp, element);
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * sortstack()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int>&sp
 * Returns : void
 */
void sortstack(stack<int>&sp){
    if(sp.empty()){
        return;
    }
    int temp= sp.top();
    // Matching bracket — pop from stack
    sp.pop();
    sortstack(sp);
    insertinstack(sp, temp);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Stack Practice 2
 */
int main(){
    stack<int>sp;
    // Opening bracket — push onto stack
    sp.push(9);
    // Opening bracket — push onto stack
    sp.push(8);
    // Opening bracket — push onto stack
    sp.push(5);
    // Opening bracket — push onto stack
    sp.push(12);
    // Opening bracket — push onto stack
    sp.push(10);
    int size= sp.size();
    int mid;
    if(size&1){
         mid= sp.size()/2 +1;
    }
    else{
        mid= sp.size()/2;
    }
    int element;
    sortstack(sp);
    
    // Iterate over all elements
    for(int i=0; i< size; i++){
        cout<< sp.top()<< endl;
        // Matching bracket — pop from stack
        sp.pop();
    }
}
