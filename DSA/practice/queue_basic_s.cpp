/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : queue_basic_s.cpp
 * PROBLEM  : Queue Basic S
 * ABOUT    : General practice and mixed problems
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Queue{
    public:
    int size= 5;
    int arr[5];
    int front;
    int rear;
    Queue(){
        front = -1;
        rear= -1;
        bool isEmpty(); 
        bool isFull();
    }
     
     
     /*
      * isEmpty()
      * Purpose : Standard DSA solution for this problem.
      * Returns : bool
      */
     bool isEmpty() {
        if(front== -1|| front> rear){
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
        if(rear== size-1){
            return true;
        }
        else{
            return false;
        }
    }
    
    
    /*
     * enqueue()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int data
     * Returns : void
     */
    void enqueue(int data){
        if(isFull()){
            cout<< "Can't enqueue "<< data<< " in the queue"<< endl;
        }
        else {
            front =0;
            rear++;
            arr[rear]= data;
            cout<< "enqueued "<< data<< endl;
        }
    }
    
    
    /*
     * dequeue()
     * Purpose : Standard DSA solution for this problem.
     * Returns : int
     */
    int dequeue(){
        if(isEmpty()){
            cout<< "Can't dequeue "<< endl;
            return -1;
        }
        else {
            int x = arr[front];
            front++;
            cout<< "dequeued "<< x<< "from the queue "<< endl;
            
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Queue Basic S
 */
int main(){
    Queue* q= new Queue();
    q-> enqueue(10);
    q-> enqueue(20);
    q-> enqueue(30);
    q-> enqueue(40);
    q-> enqueue(50);
    q-> enqueue(60);
    q-> dequeue();


}
