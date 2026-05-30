/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : deque_implementation.cpp
 * PROBLEM  : Deque Implementation
 * LEETCODE : 239 — Sliding Window Maximum (deque pattern)
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class DEqueue{
    public:
    int *arr;
    int front;
    int rear;
    int size;

    DEqueue(int s){
        this-> size= s;
        front=-1;
        rear=-1;
        arr= new int[size];
    }
    
    
    /*
     * isfull()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : bool
     */
    bool isfull(){
        if((rear== size-1 && front==0)|| (rear== front-1)){
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
     * pushrear()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Params  : int data
     * Returns : void
     */
    void pushrear(int data){
        if(isfull()){
            cout<< "overflow"<< endl;
        }
        else if(rear== size-1 && front!=0){
            rear=0;
            arr[rear]= data;
        }
        else {
            if(front ==-1){
                front=0;
            }
            rear++;
            arr[rear]= data;
        }
    }
    
    
    /*
     * popfront()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void popfront(){
        if(isempty()){
            cout<< "underflow"<< endl;
        }
        else if(front== rear){
            arr[front]=-1;
            front= -1;
            rear= -1;
        }
        else if(front==size-1){
            arr[front]=-1;
            front=0;
        }
        else{
            arr[front]=-1;
            front++;
        }
    }
    
    
    /*
     * pushfront()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Params  : int data
     * Returns : void
     */
    void pushfront(int data){
        if(isfull()){
            cout<< "overflow"<< endl;
        }
        else if(front==-1 && rear== -1){
            front=rear=0;
            arr[front]= data;
        }
        else if(front== 0 && rear!=size-1){
            front=size-1;
            arr[front]= data;
        }
        else {
            front--;
            arr[front]= data;
        }
    }
    
    
    /*
     * poprear()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void poprear(){
        if(isempty()){
            cout<< "underflow"<< endl;
        }
        else if(rear== front){
            arr[rear]= -1;
            rear=-1;
            front=-1;
        }
        else if(rear== 0){
            rear= size-1;
        }
        else {
            arr[rear]=-1;
            rear--;
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
 * Purpose : Entry point — demo/test for Deque Implementation
 */
int main(){
    DEqueue* deq= new DEqueue(5);
    deq->print();
    deq->pushrear(10);
    deq->print();
    deq->pushfront(20);
    deq->print();
    deq->pushfront(70);
    deq->print();
    deq->pushrear(50);
    deq->print();
    deq->pushfront(30);
    deq->print();
    deq->popfront();
    deq->print();
    deq->popfront();
    deq->print();
    deq->popfront();
    deq->popfront();
    deq->print();





}
