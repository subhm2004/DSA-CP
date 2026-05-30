/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : next_smaller_element.cpp
 * PROBLEM  : Next Smaller Element
 * LEETCODE : 496 — Next Greater Element I
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <vector>
using namespace std;


/*
 * nextsmaller()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : int ans[], int& index, int& size, int arr[], stack<int>&sp
 * Returns : void
 */
void nextsmaller(int ans[], int& index, int& size, int arr[], stack<int>&sp){
    while(index>=0){
        if(!sp.empty() && (sp.top() < arr[index])) {
        ans[index]= sp.top();
        // Opening bracket — push onto stack
        sp.push(arr[index]);
        index--;
        }
        else if (!sp.empty() &&  (sp.top() > arr[index])) {
            // Matching bracket — pop from stack
            sp.pop();
        }
        else {
            ans[index]= -1;
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Next Smaller Element
 */
int main(){
    int arr[]= {8,4,1,6,2,3};
    int size= 6;
    int index= size-1;
    int ans[6];
    stack<int>sp;
    // Opening bracket — push onto stack
    sp.push(-1);
    nextsmaller(ans,index,size,arr,sp);
    // Iterate over all elements
    for(int i=0; i< size; i++){
        cout<< ans[i]<< " ";
    }
}
