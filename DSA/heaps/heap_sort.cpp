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

// ════════════════════════════════════════════════════════════════════════════
// HEAP SORT — Max heap banao, root ko end pe swap, size kam karo
// ────────────────────────────────────────────────────────────────────────────
// Phase 1: buildHeap — O(n) bottom-up heapify
// Phase 2: root (max) ko last se swap, heap size--, root pe heapify
// Repeat jab tak size > 1 — array descending se sorted hota hai
// Class Heap: insert/delete demo; global heapify/buildHeap/heapsort
// ════════════════════════════════════════════════════════════════════════════

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

    // ── insert: max-heap bubble up ─────────────────────────────────────────
    void insert(int val){
        if(size== capacity){
            return;
        }
        size++;
        arr[size]= val;
        int index= size;
        while(index>1){
            int parent= size/2; // note: parent should be index/2 ideally
            if(arr[parent]< arr[index]){
                swap(arr[parent], arr[index]);
                index= parent;
            }
            else {
                break;
            }
        }
    }

    // ── printHeap: 1-indexed array print ─────────────────────────────────────
    void printHeap(){
        for(int i=1; i<= size; i++){
            cout<< arr[i]<< " ";
        }
    }

    // ── deleteHeap: root hatao, last ko root pe, bubble down ───────────────
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

// ── heapify: index i ko max-heap ke liye fix (recursive) ───────────────────
//   1) left, right children compare — largest pick
//   2) largest != i -> swap, recursively heapify largest child pe
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

// ── buildHeap: size/2 se 1 tak heapify — O(n) ──────────────────────────────
void buildHeap(int arr[], int size){
    for(int i= size/2; i>0; i--){
        heapify(arr,i,size);
    }
}

// ── heapsort: max extract repeatedly — descending sort ─────────────────────
//   1) jab tak size != 1: arr[1] aur arr[size] swap
//   2) size--, root pe heapify
void heapsort(int arr[], int size){
    while(size!=1){
        swap(arr[1], arr[size]);
        size--;
        heapify(arr,1,size);

    }
}
