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

// ════════════════════════════════════════════════════════════════════════════
// BUILD HEAP + HEAP SORT — Complete pipeline demo
// ────────────────────────────────────────────────────────────────────────────
// arr[0] dummy (-1), actual heap arr[1..size]
// buildHeap: O(n) — last internal node se root tak Heapify
// HeapSort: max ko end pe swap, size kam, root heapify
// Class Heap: insert/delete/print for interactive demo
// ════════════════════════════════════════════════════════════════════════════

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

    // ── insert: max-heap bubble up ─────────────────────────────────────────
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

    // ── HeapPrint: array print (0-indexed loop) ────────────────────────────
    void HeapPrint(){
        for(int i=0; i<size; i++){
            cout<< arr[i]<< " ";
        }
    }

    // ── deleteHeap: root extract, bubble down ──────────────────────────────
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

// ── Heapify: index pe bubble down (recursive) ──────────────────────────────
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

// ── buildHeap: size/2 se 1 tak Heapify ─────────────────────────────────────
void buildHeap(int arr[], int size){
            for(int i=size/2; i>0; i--){
                Heapify(arr,i,size);
            }

}

// ── HeapSort: root-end swap loop ─────────────────────────────────────────────
void HeapSort(int arr[], int size){
            while(size >0){
                swap(arr[1], arr[size]);
                size--;
                Heapify(arr,1, size);
              
            }
}

// ── main: buildHeap print, phir HeapSort aur sorted print ────────────────────
int main(){
    int arr[]= {-1,12,56,43,6,78,87,5,44,3,23,32};
    int size= 11;
    buildHeap(arr,size);
    cout<< "Printing Heap"<< endl;
    for(int i=0; i<= size; i++){
        cout<< arr[i]<<" ";
    }
    cout<< endl;
    HeapSort(arr, size);
    cout<< "Printing Heap after sorting"<< endl;
    for(int i=0; i<= size; i++){
        cout<< arr[i]<<" ";
    }




    

}
