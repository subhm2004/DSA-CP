/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : n_stacks_in_array.cpp
 * PROBLEM  : N Stacks In Array
 * LEETCODE : 716 — Max Stack (multi-stack design)
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class NStack{
    public:
    int *arr, *top, *next;
    int number;
    int freespot;
    int size;
    NStack(int n, int s){
        this-> size= s;
        number= n;
        arr= new int[size];
        top= new int[number];
        next= new int[size];
        freespot=0;
        for(int i=0; i<number; i++){
            top[i]= -1;
        }
        // Iterate over all elements
        for(int i=0; i<size; i++){
            next[i]= i+1;
        }
        next[size-1]= -1;
    }
    
    
    /*
     * push()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int data, int m
     * Returns : void
     */
    void push(int data, int m){
        if(freespot==-1){
            cout<< "Can't be pushed"<< endl;
        }
        else {
            int index= freespot;
            freespot= next[index];
            arr[index]= data;
            next[index]= top[m-1];
            top[m-1]= index;
        }
    }
    
    
    /*
     * pop()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int m
     * Returns : int
     */
    int pop(int m){
        if(top[m-1] ==-1){
            return -1;
        }
        else {
            int index= top[m-1];
            top[m-1]= next[index];
            next[index]= freespot;
            freespot= index;
            return arr[index];

        }

    }
    ~NStack(){
        delete []arr;
        delete []top;
        delete []next;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for N Stacks In Array
 */
int main(){
    NStack* st= new NStack(2,6);
}
