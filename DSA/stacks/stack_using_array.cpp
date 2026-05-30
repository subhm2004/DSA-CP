/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : stack_using_array.cpp
 * PROBLEM  : Stack Using Array
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
    int size;
    int top;
    Stack(int size){
        int *arr= new int[size];
        this-> size= size;
        this-> top= -1;
    }
    
    
    /*
     * push()
     * Purpose : LIFO stack — push on open, pop on match.
     * Params  : int data
     * Returns : void
     */
    void push(int data){
        if(top == size-1){
            cout<< "stack overflow"<< endl;
            return;
        }
        else {
            top= top + 1;
            arr[top]= data;
        }
    }
    
    
    /*
     * pop()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int pop(){
        if(top== -1){
            cout<< "stack underflow can't delete"<< endl;
            return INT_MIN;
        }
        else {
            int x= arr[top];
            top= top-1;
            return x;
        }
    }
    
    
    /*
     * gettop()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int gettop(){
        if(top == -1){
            cout<< "stack underflow"<< endl;
            return INT_MAX;
        }
        else {
            return arr[top];
        }
    }
    
    
    /*
     * getsize()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : int
     */
    int getsize(){
        if(top==-1){
            cout<< "Stack is empty"<< endl;
        }
        else {
            return top+1;
        }
    }
    
    
    /*
     * isEmpty()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : bool
     */
    bool isEmpty(){
        if(top==-1){
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
        if(top== size-1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * print()
     * Purpose : LIFO stack — push on open, pop on match.
     * Returns : void
     */
    void print(){
        cout<< "Stack:"<< endl;
        for(int i=top; i>=0; i--){
            cout<< arr[i]<< endl;
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Stack Using Array
 */
int main(){
    cout<< "Name: Vanshika Aggarwal"<< endl;
    cout<< "Roll No. 22001003138"<< endl;
    Stack* sp= new Stack(5);
    sp-> push(10);
    sp-> push(20);
    sp-> push(30);
    sp-> push(40);
    sp-> push(50);
    sp-> print();
    cout<< "Size of stack is: "<< sp-> getsize() << endl;
    cout<< "Is stack full: "<< sp-> isfull()<< endl;
    cout<< "popped: "<< sp-> pop()<< " from stack "<< endl;
    cout<< "New stack is:"<< endl;
    sp-> print();   
}
