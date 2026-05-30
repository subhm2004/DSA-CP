/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : online_stock_span.cpp
 * PROBLEM  : Online Stock Span
 * LEETCODE : 901 — Online Stock Span
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <utility>
#include <stack>
using namespace std;
stack<pair<int,int>>st;


/*
 * next()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : int price
 * Returns : int
 */
int next(int price){
    int span=1;
    while(!st.empty() && st.top().first <= price){
        span= span + st.top().second;
        st.pop();
    }
    st.push({price,span});
    return span;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Online Stock Span
 */
int main(){
    int price;
    cin>> price;
    int ans= next(price);
    cout<< ans;
}
