/*
 * ============================================================================
 * TOPIC    : Queues
 * FILE     : sliding_window_maximum.cpp
 * PROBLEM  : Sliding Window Maximum
 * LEETCODE : 239 — Sliding Window Maximum
 * ABOUT    : Queue, deque, circular queue, sliding window
 * APPROACH : Deque/map maintains window min/max in O(n).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <deque>
using namespace std;


/*
 * printfirstnegative()
 * Purpose : FIFO queue — enqueue rear, dequeue front.
 * Params  : int *arr, int& size, int&k
 * Returns : void
 */
void printfirstnegative(int *arr, int& size, int&k){
    deque<int>dq; // store the index of negative number
    for(int i=1; i<=k; i++){
        if(arr[i]<0){
            dq.push_back(i);
        }
    }
    // Iterate over all elements
    for(int i=k+1; i<=size; i++){
        if(dq.empty()){
        cout<< 0<< " ";
        }
        else {
        cout<< arr[dq.front()]<< " ";
        }
        if(i-dq.front()>=k){
            dq.pop_front();
        }
        if(arr[i]<0){
            dq.push_back(i);
        }
    }
    if(dq.empty()){
        cout<< 0<< " ";
    }
    else {
        cout<< arr[dq.front()]<< " ";
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Sliding Window Maximum
 */
int main(){
    int arr[]= {2,-5,4,-1,-2,0,5};
    int size= 7;
    int k=3; // window size
    printfirstnegative(arr,size,k);



}
