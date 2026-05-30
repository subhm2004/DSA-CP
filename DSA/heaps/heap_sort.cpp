/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : heap_sort.cpp
 * PROBLEM  : Heap Sort
 * LEETCODE : 912 — Sort an Array (heap sort approach)
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Heap{
    public:
    int size;
    int capacity;
    int *arr;
    Heap(int capacity){
        this-> size=0;
        this-> capacity= capacity;
        this-> arr= new int[capacity];
    }
    
    
    /*
     * insert()
     * Purpose : priority_queue for O(log n) min/max access.
     * Params  : int val
     * Returns : void
     */
    void insert(int val){
        if(size== capacity){
            return;
        }
        size++;
        arr[size]= val;
        int index= size;
        while(index>1){
            int parent= size/2;
            if(arr[parent]< arr[index]){
                swap(arr[parent], arr[index]);
                index= parent;
            }
            else {
                break;
            }
        }
    }
    
    
    /*
     * printHeap()
     * Purpose : Build heap; repeatedly extract min/max.
     * Returns : void
     */
    void printHeap(){
        // Iterate over all elements
        for(int i=1; i<= size; i++){
            cout<< arr[i]<< " ";
        }
    }
    
    
    /*
     * deleteHeap()
     * Purpose : Build heap; repeatedly extract min/max.
     * Returns : void
     */
    void deleteHeap(){
        arr[1]= arr[size];
        size--;
        int index=1;
        while(index< size){
            int left= 2*index;
            int right= 2*index+1;
            int largest= index;
            if(left<= size && arr[largest]< arr[left]){
                largest= left;
            }
            if(right<= size && arr[largest]< arr[right]){
                largest= right;
            }
            if(largest!=index){
                swap(arr[largest], arr[index]);
                index= largest;
            }
            else {
                break;
            }
        }       
    }
};


/*
 * heapify()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : int arr[], int index, int size
 * Returns : void
 */
void heapify(int arr[], int index, int size){
    int left= 2*index;
    int right= 2*index+1;
    int largest= index;
    if(left<= size && arr[largest]< arr[left]){
        largest= left;
    }
    if(right<= size && arr[largest]< arr[right]){
        largest= right;
    }
    if(largest!= index){
        swap(arr[largest], arr[index]);
        index= largest;
        heapify(arr,index,size); 
    }
}


/*
 * buildHeap()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : int arr[], int size
 * Returns : void
 */
void buildHeap(int arr[], int size){
    // Iterate over all elements
    for(int i= size/2; i>0; i--){
        heapify(arr,i,size);
    }
}


/*
 * heapsort()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : int arr[], int size
 * Returns : void
 */
void heapsort(int arr[], int size){
    while(size!=1){
        swap(arr[1], arr[size]);
        size--;
        heapify(arr,1,size);

    }
}
