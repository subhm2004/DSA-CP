/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_basics.cpp
 * PROBLEM  : Stack Basics
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * findmid()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : stack<int> &sp, int temp, int position
 * Returns : void
 */
void findmid(stack<int> &sp,int temp,int position ){
    if(position==1) {
        cout<< temp<< endl;
        return;
    }
    // Matching bracket — pop from stack
    sp.pop();
    findmid(sp,sp.top(), position-1);
    // Opening bracket — push onto stack
    sp.push(temp);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Stack Basics
 */
int main(){
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
    // Opening bracket — push onto stack
    sp.push(60);
    int position;
    int temp= sp.top();
    if(sp.size()&1){ 
        position = sp.size() /2 +1;    
    }
    else{
        position= sp.size()/2 ;    
    }
    findmid(sp,temp,position);
    


}
