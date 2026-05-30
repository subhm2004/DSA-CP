/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_practice_1.cpp
 * PROBLEM  : Stack Practice 1
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;


/*
 * nextsmaller()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : int arr[], int ans[], int& size
 * Returns : void
 */
void nextsmaller(int arr[], int ans[], int& size){
    int i= size-1;
    stack<int>st;
    st.push(-1);
    while(i>=0){
        if(!st.empty() && arr[i] > st.top()){
            ans[i]= st.top();
            st.push(arr[i]);
            i--;
        }
        else {
            st.pop();
        }
        
    }
    cout<< "{";
    // Iterate over all elements
    for(int i=0; i< size; i++){
        cout<< ans[i]<< " ";
    }
    cout<< "}";
}


/*
 * prevsmaller()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : int arr[], int ans[], int& size
 * Returns : void
 */
void prevsmaller(int arr[], int ans[], int& size){
    int i=0;
    stack<int>st;
    st.push(-1);
    while(i< size){
        if(!st.empty() && arr[i]> st.top()){
            ans[i]= st.top();
            st.push(arr[i]);
            i++;
        }
        else {
            st.pop();
        }
    }
    cout<< "{";
    // Iterate over all elements
    for(int i=0; i< size; i++){
        cout<< ans[i]<< " ";
    }
    cout<< "}";

}



/*
 * main()
 * Purpose : Entry point — demo/test for Stack Practice 1
 */
int main(){
    int arr[]= {8,4,6,2,3};
    int size= 5;
    int ans[5];
    prevsmaller(arr,ans,size);
}
