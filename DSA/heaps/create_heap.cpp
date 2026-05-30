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
    
    
    /*
     * insert()
     * Purpose : priority_queue for O(log n) min/max access.
     * Params  : int val
     * Returns : void
     */
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
                swap(arr[parent], arr[index]);
                index = parent;
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
        for(int i=0; i<= size; i++){
            cout<< arr[i]<< " ";
        }
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Create Heap
 */
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
