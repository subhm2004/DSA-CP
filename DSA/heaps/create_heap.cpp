/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : create_heap.cpp
 * PROBLEM  : Create Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CREATE MAX HEAP — Array-based 1-indexed heap insert
// ────────────────────────────────────────────────────────────────────────────
// arr[1..size] me store — parent index/2, children 2*i, 2*i+1
// Insert: end pe daalo, parent se swap jab tak parent chhota ho
// Max heap property: parent >= dono children
// ════════════════════════════════════════════════════════════════════════════

class Heap{
    public:
    int size;
    int *arr;
    int capacity;
    Heap(int capacity){
        this-> size=0;
        this-> arr= new int[capacity];
        this-> capacity= capacity;
    }

    // ── insert: naya element max-heap me add ───────────────────────────────
    //   1) overflow check — size == capacity
    //   2) size++, arr[index]=val (1-indexed)
    //   3) parent se compare — parent chhota ho to swap
    //   4) index = parent tak bubble up
    void insert(int val){
        if(size== capacity){
            cout<< "heap overflow"<< endl;
            return;
        }
        size++;
        int index= size;
        arr[index]= val;
        while(index>1){
            int parent= index/2;
            if(arr[parent] < arr[index]){
                swap(arr[parent], arr[index]); // parent chhota — upar bhejo
                index = parent;
            }
            else {
                break; // heap property satisfied
            }
        }
    }

    // ── printHeap: saare stored elements print ─────────────────────────────
    //   1) i=0 se size tak loop — heap array dikhata hai
    void printHeap(){
        for(int i=0; i<= size; i++){
            cout<< arr[i]<< " ";
        }
    }
};

// ── main: insert demo values aur print ───────────────────────────────────────
int main(){
    Heap h(10);
    h.insert(10);
    h.insert(1);
    h.insert(11);
    h.insert(15);
    h.insert(5);
    h.insert(6);
    cout<< "Printing heap: "<< endl;
    h.printHeap();

}
