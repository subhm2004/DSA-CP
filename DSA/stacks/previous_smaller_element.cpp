/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : previous_smaller_element.cpp
 * PROBLEM  : Previous Smaller Element
 * LEETCODE : 503 — Next Greater Element II
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
 * prevsmallerelement()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : int arr[], int& index, int& size
 * Returns : void
 */
void prevsmallerelement(int arr[], int& index, int& size){
    stack<int>sp;
    vector<int>ans;
    // Opening bracket — push onto stack
    sp.push(-1);
    while(index< size){
        if(!sp.empty() && (sp.top()< arr[index])){
            ans.push_back(sp.top());
            // Opening bracket — push onto stack
            sp.push(arr[index]);
            index++;
        }
        else {
            // Matching bracket — pop from stack
            sp.pop();
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Previous Smaller Element
 */
int main(){
    int arr[]= {8,4,6,1,2,3};
    int size= 6;
    int index= 0;
}
