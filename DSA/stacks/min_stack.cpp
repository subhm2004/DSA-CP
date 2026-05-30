/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : min_stack.cpp
 * PROBLEM  : Min Stack
 * LEETCODE : 155 — Min Stack
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;
class minStack{
    vector<pair<int,int>>sp;
    
    
    /*
     * push()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int data
     * Returns : void
     */
    void push(int data){
        if(sp.empty()){
            pair<int,int>p;
            p.first= data;
            p.second= data;
            // Opening bracket — push onto stack
            sp.push_back(p);
        }
        else {
            pair<int,int>p;
            int prevmin= sp.back().second;
            p.second= min(prevmin, data);
            p.first= data;
            // Opening bracket — push onto stack
            sp.push_back(p);
        }
    }
    
    
    /*
     * pop()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void pop(){
        if(!sp.empty()){
            sp.pop_back();
        }
    }
    
    
    /*
     * topvalue()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int topvalue(){
        if(!sp.empty()){
            return sp.back().first;
        }
    }
    
    
    /*
     * getmin()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int getmin(){
        if(!sp.empty()){
            return sp.back().second;
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Min Stack
 */
int main(){
   

}
