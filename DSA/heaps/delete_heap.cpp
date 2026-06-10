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

// ════════════════════════════════════════════════════════════════════════════
// DELETE FROM HEAP + HEAP SORT — Root delete aur full sort pipeline
// ────────────────────────────────────────────────────────────────────────────
// deleteElement: last -> root, bubble down (largest child)
// Heapify/buildHeap/HeapSort: global functions on 1-indexed array
// HeapSort: har step pe max root ko end pe bhejo
// ════════════════════════════════════════════════════════════════════════════

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

    // ── insert: max-heap me bubble up ──────────────────────────────────────
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

    // ── deleteElement: root delete, bubble down ──────────────────────────────
    //   1) arr[1]=arr[size], size--
    //   2) largest among self/left/right dhundho
    //   3) swap aur index=largest jab tak fix na ho
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

// ── Heapify: subtree root index ko max-heap fix ──────────────────────────────
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

// ── buildHeap: bottom-up — i=size/2 se 1 tak Heapify ───────────────────────
void buildHeap(int arr[], int size){
    for(int i= size/2; i>0; i--){
        Heapify(arr,size,i);
    }
}

// ── HeapSort: swap root-end, shrink, Heapify root ───────────────────────────
void HeapSort(int arr[], int size){
    while(size >0){
        swap(arr[1], arr[size]);
        size--;
        Heapify(arr,size,1);
    }
}
