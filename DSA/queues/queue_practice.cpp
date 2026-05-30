/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : queue_practice.cpp
 * PROBLEM  : Queue Practice
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : FIFO queue — enqueue rear, dequeue front.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class DEQueue{
    public:
    int *arr;
    int front;
    int rear;
    int size;
    DEQueue(int s){
        this-> size= s;
        this-> front=-1;
        this-> rear=-1;
        arr= new int[size];
    }
    
    
    /*
     * pushback()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Params  : int data
     * Returns : void
     */
    void pushback(int data){
        if((rear== size-1&& front==0)|| (rear+1== front)){
            cout<< "Queue Overflow"<< endl;
        }
        else if(front==-1){
            front=0;
            rear++;
            arr[rear]= data;
        }
        else if(front!=0 && rear==size-1){
            rear=0;
            arr[rear]= data;
        }
        else {
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
        if(front==-1 && rear==-1){
            cout<< "Queue underflow"<< endl;
        }
        else if(front== rear){
            arr[front]=-1;
            front=-1;
            rear=-1;
        }
        else if(front== size-1){
            arr[front]=-1;
            front=0;
        }
        else {
            arr[front]=-1;
            front++;
        }
    }
    
    
    /*
     * popback()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Returns : void
     */
    void popback(){
        if(front==-1 && rear==-1){
            cout<< "Queue Overflow"<< endl;
        }
        else if(front== rear){
            arr[rear]=-1;
            rear=-1;
            front=-1;
        }
        else if(rear==0){
            arr[rear]= -1;
            rear= size-1; 
        }
        else {
            arr[rear]=-1;
            rear--;
        }
    }
    
    
    /*
     * pushfront()
     * Purpose : FIFO queue — enqueue rear, dequeue front.
     * Params  : int data
     * Returns : void
     */
    void pushfront(int data){
        if((front==0 && rear==size-1)||(rear+1== front)){
            cout<< "Queue Overflow"<< endl;
        }
        else if(front==-1 && rear==-1){
            front++;
            rear++;
            arr[front]= data;
        }
        else if(front==0 && rear!= size-1){
            front= size-1;
            arr[front]= data;
        }
        else{
            front--;
            arr[front]=data;
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Queue Practice
 */
int main(){

}
