/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : build_heap.cpp
 * PROBLEM  : Build Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Heap{
    public:
    int *arr;
    int size;
    int capacity;
    Heap(int capacity){
        this-> size= 0;
        this-> arr= new int[capacity];
        this-> capacity= capacity;
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
     * HeapPrint()
     * Purpose : Build heap; repeatedly extract min/max.
     * Returns : void
     */
    void HeapPrint(){
        // Iterate over all elements
        for(int i=0; i<size; i++){
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
        int index= 1;
        while(index< size){
            int largest= index;
            int left= 2*index;
            int right= 2*index+1;
            if(left<= size && arr[largest]< arr[left]){
                largest= left;
            }
            if(right<= size && arr[largest]< arr[right]){
                largest= right;
            }
            if(largest!= index){
                swap(arr[largest], arr[index]);
                index = largest;
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
 * Params  : int arr[], int index, int size
 * Returns : void
 */
void Heapify(int arr[], int index, int size){
            int largest= index;
            int left= 2* index;
            int right= 2*index+1;
            if(left<= size && arr[largest]< arr[left] ){
                largest= left;
            }
            if(right<= size && arr[largest]< arr[right]){
                largest= right;
            }
            if(largest!= index){
                swap(arr[largest], arr[index]);
                index= largest;
                Heapify(arr,index,size);
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
            for(int i=size/2; i>0; i--){
                Heapify(arr,i,size);
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
                Heapify(arr,1, size);
              
            }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Build Heap
 */
int main(){
    int arr[]= {-1,12,56,43,6,78,87,5,44,3,23,32};
    int size= 11;
    buildHeap(arr,size);
    cout<< "Printing Heap"<< endl;
    // Iterate over all elements
    for(int i=0; i<= size; i++){
        cout<< arr[i]<<" ";
    }
    cout<< endl;
    HeapSort(arr, size);
    cout<< "Printing Heap after sorting"<< endl;
    // Iterate over all elements
    for(int i=0; i<= size; i++){
        cout<< arr[i]<<" ";
    }




    

}
