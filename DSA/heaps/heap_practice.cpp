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

// ════════════════════════════════════════════════════════════════════════════
// HEAP CLASS PRACTICE — Insert, delete, heapify, buildHeap
// ────────────────────────────────────────────────────────────────────────────
// 1-indexed array: arr[1..size], parent=i/2, left=2i, right=2i+1
// Insert: bubble up — parent se swap jab parent chhota ho
// Delete root: last element root pe, bubble down (largest child se swap)
// buildHeap: last non-leaf se heapify (O(n))
// ════════════════════════════════════════════════════════════════════════════

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

    // ── insert: max-heap me element add ────────────────────────────────────
    //   1) overflow check
    //   2) size++, arr[size]=data, index=size
    //   3) parent < current ho to swap, index=parent
    //   4) parent >= current pe break — heap property OK
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

    // ── printHeap: arr[1..size] print ──────────────────────────────────────
    void printHeap(){
        for(int i=1; i<=size; i++){
            cout<< arr[i]<< " ";
        }
    }

    // ── deleteHeap: root extract aur heapify down ──────────────────────────
    //   1) ans=arr[1], arr[1]=arr[size], size--
    //   2) index=1 se niche: left/right me sabse bada dhundho
    //   3) largest != index -> swap, index=largest
    //   4) warna break — ans return (deleted max)
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

    // ── Heapify: arr[i] ko max-heap property ke liye fix ──────────────────
    //   1) left/right children se largest dhundho
    //   2) largest != index -> swap, recursively Heapify
    //   3) leaf/subtree OK pe return
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

    // ── buildHeap: array ko max-heap banao ─────────────────────────────────
    //   1) i=n/2 se 1 tak (last internal node se root tak)
    //   2) left/right se largest pick, swap agar zaroori
    //   3) swap ke baad Heapify call — subtree fix
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

// ── main: insert values aur print heap ───────────────────────────────────────
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
