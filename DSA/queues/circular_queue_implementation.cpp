/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : circular_queue_implementation.cpp
 * PROBLEM  : Circular Queue Implementation
 * LEETCODE : 622 — Design Circular Queue
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class CQueue{
    public:
    int front;
    int rear;
    int *arr;
    int size;
    CQueue(int s){
        this-> size=s;
        this-> front=-1;
        this-> rear= -1;
        arr= new int[size];
    }
    
    
    /*
     * isfull()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : bool
     */
    bool isfull(){
        if((rear== size-1 && front== 0) || (rear== front-1)){
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
        if(front==-1 && rear== -1){
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
        else if (rear== size-1 && front!= 0) {
            rear=0;
            arr[rear]= data;
        }
        else {
            if(front== -1 && rear== -1){
                front=0;
            }
            rear++;
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
            cout<< "stack underflow"<< endl;
        }
        else if(front == rear){
            arr[front]=-1;
            front=-1;
            rear=-1;
        }
        if(front== size-1){
            front=0;
        }
        else {
            arr[front]=0;
            front++;
        }
    }
    
    
    /*
     * print()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void print(){
        cout<< "front: "<< front<< endl;
        cout<< "rear: "<< rear<< endl;
        // Iterate over all elements
        for(int i=0; i< size; i++){
            cout<< arr[i]<< " ";
        }
        cout<< endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Circular Queue Implementation
 */
int main(){
    CQueue* cq= new CQueue(5);
    cq-> push(10);
    cq-> print();

    cq-> push(20);
    cq-> print();

    cq-> push(30);
    cq-> print();

    cq-> push(40);
    cq-> print();
    cq-> push(50);
    cq-> print();

    cq-> pop();
    cq-> print();

    cq-> push(50);
    cq-> print();

}
