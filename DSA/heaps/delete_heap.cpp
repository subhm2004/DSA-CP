/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : delete_heap.cpp
 * PROBLEM  : Delete Heap
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
        this-> capacity= capacity;
        this-> size= 0;
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
            cout<< "Overflow"<< endl;
            return;
        }
        size++;
        arr[size]= val;
        int index= size;
        while(index>1){
            int parent= index/2;
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
     * deleteElement()
     * Purpose : priority_queue for O(log n) min/max access.
     * Returns : void
     */
    void deleteElement(){
        arr[1]= arr[size];
        size--;
        int index=1;
        while(index< size){
            int largest= index;
            int left= 2* index;
            int right= 2* index+1;
            if(left<= size && arr[largest] < arr[left]){
                largest= left;
            }
            if(right<= size && arr[largest] < arr[right]){
                largest= right;
            }
            if(largest!= index){
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
 * Heapify()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : int arr[], int size, int index
 * Returns : void
 */
void Heapify(int arr[], int size, int index){
    int largest= index;
    int left= 2* index;
    int right= 2* index+ 1;
    if(left<= size && arr[largest]< arr[left]){
        largest= left;
    }
    if(right<= size && arr[largest]< arr[right]){
        largest= right;
    }
    if(largest!= index){
        swap(arr[largest], arr[index]);
        index= largest;
        Heapify(arr, size, index);
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
        Heapify(arr,size,i);
    }
}


/*
 * HeapSort()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : int arr[], int size
 * Returns : void
 */
void HeapSort(int arr[], int size){
    while(size >0){
        swap(arr[1], arr[size]);
        size--;
        Heapify(arr,size,1);
    }
}
