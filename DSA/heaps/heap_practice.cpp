/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : heap_practice.cpp
 * PROBLEM  : Heap Practice
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
    int*arr;
    int capacity;
    Heap(int capacity){
        this-> capacity= capacity;
        this-> size=0;
        this-> arr= new int[capacity];
    }
    
    
    /*
     * insert()
     * Purpose : priority_queue for O(log n) min/max access.
     * Params  : int data
     * Returns : void
     */
    void insert(int data){
        if(size== capacity){
            cout<< "Heap overflow"<< endl;
            return;
        }
        size++;
        arr[size]= data;
        int index= size;
        while(index>1){
            int parent= index/2;
            if(arr[parent]< arr[index]){
                swap(arr[index], arr[parent]);
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
        for(int i=1; i<=size; i++){
            cout<< arr[i]<< " ";
        }
    }
    
    
    /*
     * deleteHeap()
     * Purpose : Build heap; repeatedly extract min/max.
     * Returns : int
     */
    int deleteHeap(){
        int ans= arr[1];
        arr[1]= arr[size];
        size--;
        int index=1;
        while(index< size){
            int left_index= 2*index;
        int right_index= 2*index+1;
        int largest= index;
        if(left_index<size && arr[left_index]> arr[largest]){
            largest= left_index;
        }
        if(right_index< size && arr[right_index]> arr[largest]){
            largest= right_index;
        }
        if(largest== index){
            break;
        }
        else {
            swap(arr[largest], arr[index]);
            index= largest;
        }

        }
        return ans;
    }
    
    
    /*
     * Heapify()
     * Purpose : Build heap; repeatedly extract min/max.
     * Params  : int arr[], int i, int size
     * Returns : void
     */
    void Heapify(int arr[], int i, int size){
        int index= i;
        int leftIndex= 2*index;
        int rightIndex= 2*index+1;
        int largest= index;
        if(leftIndex< size && arr[leftIndex]> arr[largest]){
            largest= leftIndex;
        }
        if(rightIndex< size && arr[rightIndex]> arr[largest]){
            largest= rightIndex;
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
     * Params  : int n
     * Returns : void
     */
    void buildHeap(int n){

        for(int i= n/2; i>=1; i--){
            int largest= i;
            int left= 2*i;
            int right= 2*i+1;
            if(left<= size && arr[largest]< arr[left]){
                largest= left;
            }
            if(right<= size && arr[largest]< arr[right]){
                largest= right;
            }
            if(largest!= i){
                swap(arr[largest], arr[i]);
                i= largest;
                Heapify(arr,i,size);
            }

        }

    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Heap Practice
 */
int main(){
    Heap h(10);
    h.insert(10);
    h.insert(1);
    h.insert(11);
    h.insert(15);
    h.insert(5);
    h.insert(6);
    h.printHeap();

}
