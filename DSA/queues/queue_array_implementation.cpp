/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : queue_array_implementation.cpp
 * PROBLEM  : Queue Array Implementation
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Queue{
    public:
    int *arr;
    int size;
    int front;
    int rear;
    Queue(int s){
        this-> size= s;
        this-> front =-1;
        this-> rear= -1;
        arr= new int[size];
    }
    
    
    /*
     * isfull()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : bool
     */
    bool isfull(){
        if(rear== size-1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * isempty()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : bool
     */
    bool isempty(){
        if(front== -1 && rear== -1){
            return true;
        }
        else {
            return false;
        }
    }
    
    
    /*
     * push()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Params  : int data
     * Returns : void
     */
    void push(int data){
        if(isfull()){
            cout<< "queue overflow"<< endl;
        }
        else {
            rear++;
            if(front == -1){
                front=0;
            }
            arr[rear]= data;
        }
    }
    
    
    /*
     * pop()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void pop(){
        if(isempty()){
            cout<< "queue underflow"<< endl;
        }
        else {
            if(front== rear){
                front= -1;
                rear= -1;
            }
            else {
                arr[front]=0;
                front++;
            }
        }
    }
    
    
    /*
     * getfront()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : int
     */
    int getfront(){
        if(!isempty()){
            return arr[front];
        }
    }
    
    
    /*
     * getrear()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : int
     */
    int getrear(){
        if(!isempty()){
            return arr[rear];
        }
    }
    
    
    /*
     * printqueue()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void printqueue(){
        cout<< "front is: "<< front<< endl;
        cout<< "rear is: "<< rear<< endl;
        // Iterate over all elements
        for(int i=0; i< size; i++){
            cout<< arr[i]<< " ";
        }
    }

};


/*
 * main()
 * Purpose : Entry point — demo/test for Queue Array Implementation
 */
int main(){
    Queue* q= new Queue(8);
    q->push(10);
    q->push(20);
    q->push(30);
    q->printqueue();
    cout<< endl;
    q->push(40);
    q->push(50);
    q->printqueue();
    cout<< endl;
    q->pop();
    q->printqueue();

}
