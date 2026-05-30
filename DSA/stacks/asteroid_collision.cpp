/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : asteroid_collision.cpp
 * PROBLEM  : Asteroid Collision
 * LEETCODE : 735 — Asteroid Collision
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;


/*
 * asteroidarray()
 * Purpose : LIFO stack — push on open, pop on match.
 * Params  : vector<int>&asteroids
 * Returns : void
 */
void asteroidarray(vector<int>&asteroids){
    stack<int> st;
    st.push(asteroids[0]);
    int index=1;
    while(index<asteroids.size()){
        if(asteroids[index]< 0 && st.top()>0){
            int element= max(abs(asteroids[index]), abs(st.top()));
            st.pop();
            st.push(element);
        }
        else {
            st.push(asteroids[index]);
        }
        index++;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Asteroid Collision
 */
int main(){
    vector<int>asteroids= {1,-2,10,-5};


}
