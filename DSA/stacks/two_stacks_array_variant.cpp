/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : two_stacks_array_variant.cpp
 * PROBLEM  : Two Stacks Array Variant
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : LIFO stack — push on open, pop on match.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Stack{
    public:
    int *arr;
    int size;
    int top1;
    int top2;
    Stack(int size){
        this-> size= size;
        this-> arr= new int[size];
        this-> top1 = -1;
        this-> top2= size;
    }
    
    
    /*
     * isempty1()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isempty1(){
        if(top1 == -1){
            cout<< "stack1 is empty"<< endl;
            return true;
        }
        else{
            return false;
        }
    }
    
    
    /*
     * isempty2()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isempty2(){
        if(top2== size){
            cout<< "stack2 is empty"<< endl;
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * isfull()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isfull(){
        if( top2 - top1 == 1){
            return true;
        }
        else{
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
        if(isfull()){
            cout<< "stack is full, can't push"<< endl;
            return;
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
        if(isfull()){
            cout<< "stack is full, can't push"<< endl;
            return;
        }
        else {
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
        if(isempty1()){
            cout<< "stack is empty, can't delete "<< endl;
            return;
        }
        else {
            arr[top1]= -1;
            top1--;
        }
    }
    
    
    /*
     * pop2()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void pop2(){
        if(isempty2()){
            cout<< "stack is empty, can't delete"<< endl;
            return;
        }
        else {
            arr[top2]= -1;
            top2++;
        }
    }
    
    
    /*
     * print()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void print(){
        cout<< "top1: "<< top1<< endl;
        cout<< "top2: "<< top2<< endl;
        // Iterate over all elements
        for(int i=0; i< size; i++){
            cout<< arr[i]<< " ";
        }
        cout<< endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Two Stacks Array Variant
 */
int main(){
    Stack sp(8);
    // Opening bracket — push onto stack
    sp.push1(10);
    // Opening bracket — push onto stack
    sp.push1(20);
    // Opening bracket — push onto stack
    sp.push2(30);
    // Opening bracket — push onto stack
    sp.push2(40);
    sp.pop1();
    sp.pop2();
    sp.pop1();
    sp.pop1();
    sp.print();


}
