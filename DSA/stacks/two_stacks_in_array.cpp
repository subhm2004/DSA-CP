/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : two_stacks_in_array.cpp
 * PROBLEM  : Two Stacks In Array
 * LEETCODE : 155 — Min Stack (two-stack design pattern)
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;
class Stack{
    public:
    int *arr;
    int top1;
    int top2;
    int size;
    Stack(int size){
        this-> size = size;
        arr= new int[size];
        this-> top1= -1;
        this-> top2= size;
    }
    
    
    /*
     * isEmpty()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isEmpty(){
        if(top1== -1 && top2== size){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * isFull()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isFull(){
        if(top2 == top1+1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * push1()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int data
     * Returns : void
     */
    void push1(int data){
        if(top2== top1+1){
            cout<< "Stack Overflow"<< endl;
        }
        else {
            top1++;
            arr[top1]= data;

        }
    }
    
    
    /*
     * push2()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int data
     * Returns : void
     */
    void push2(int data){
        if(top2== top1+1){
            cout<< "Stack Overflow"<< endl;
        }
        else{
            top2--;
            arr[top2]= data;
        }
    }
    
    
    /*
     * pop1()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void pop1(){
        if(top1 == -1 ){
            cout<< "Stack Underflow"<< endl;
        }
        else {
            top1--;
        }
    }
    
    
    /*
     * pop2()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void pop2(){
        if(top2== size){
            cout<< "Stack Underflow"<< endl;
        }
        else {
            top2++;
        }
    }
    
    
    /*
     * gettop1()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int gettop1(){
        if(top1== -1){
            cout<< "Stack1 Underflow"<< endl;
            return INT_MIN;
        }
        else {
            return arr[top1];
        }
    }
    
    
    /*
     * gettop2()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int gettop2(){
        if(top2== size){
            cout<< "Stack2 Underflow"<< endl;
            return INT_MIN;
        }
        else {
            return arr[top2];
        }
    }
    
    
    /*
     * print()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void print(){
        cout<< "Top1: "<< top1<< endl;
        cout<< "Top2: "<< top2<< endl;
        // Iterate over all elements
        for(int i=0; i< size; i++){
            cout<< arr[i]<< " ";
        }
        cout<< endl;
    }   
};



/*
 * main()
 * Purpose : Entry point — demo/test for Two Stacks In Array
 */
int main(){
    Stack sp(6);
    // Opening bracket — push onto stack
    sp.push1(10);
    // Opening bracket — push onto stack
    sp.push2(20);
    // Opening bracket — push onto stack
    sp.push1(30);
    // Opening bracket — push onto stack
    sp.push2(40);
    // Opening bracket — push onto stack
    sp.push1(50);
    // Opening bracket — push onto stack
    sp.push2(60);
    sp.print();
}
