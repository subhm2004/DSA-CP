/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : stack_basics_practice.cpp
 * PROBLEM  : Stack Basics Practice
 * ABOUT    : General practice and mixed problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Stack{
    public:
    int size= 5;
    int arr[5];
    int top;
    Stack(){
        top= -1;
        bool isEmpty();
        bool isFull();
        void push(int data);

    }
    
    
    /*
     * isEmpty()
     * Purpose : Standard DSA solution for this problem.
     * Returns : bool
     */
    bool isEmpty(){
        if(top== -1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * isFull()
     * Purpose : Standard DSA solution for this problem.
     * Returns : bool
     */
    bool isFull(){
        if(top== size-1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * push()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int data
     * Returns : void
     */
    void push(int data){
        if(isFull()){
            cout<< "Stack Overflow "<<" can't push "<< data<< " into the stack" <<endl;
            return;
        }
        else {
            top++;
            arr[top]= data;
            cout<< "pushed "<< data<< "in the stack "<< endl;
        }
    }
    
    
    /*
     * pop()
     * Purpose : Standard DSA solution for this problem.
     * Returns : int
     */
    int pop(){
        if(isEmpty()){
            return -1;
        }
        else {
            int x= arr[top];
            top--;
            cout<< "popped "<< x<< " from stack"<< endl;
            return x;
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Stack Basics Practice
 */
int main(){
    
    Stack* s= new Stack();
    s-> push(10);
    s-> push(20);
    s-> push(30);
    s-> push(40);
    s-> push(50);
    s-> push(60);
    

}
