/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : check_max_heap.cpp
 * PROBLEM  : Check Max Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        this-> data= val;
        this-> left= NULL;
        this-> right= NULL;
    }
};
class Valid{
    public:
    int maxVal;
    bool isHeap;
    Valid(){

    }
};


/*
 * CheckMaxHeap()
 * Purpose : Build heap; repeatedly extract min/max.
 * Params  : Node* root
 * Returns : Valid
 */
Valid CheckMaxHeap(Node* root){
    if(root== NULL){
        Valid temp;
        temp.maxVal= INT_MIN;
        temp.isHeap= true;
        return temp;
    }
    if(root-> left== NULL && root-> right== NULL){
        Valid temp;
        temp.maxVal= root-> data;
        temp.isHeap= true;
        return temp;

    }
    Valid left= CheckMaxHeap(root-> left);
    Valid right= CheckMaxHeap(root-> right);
    if(root-> data> left.maxVal && root-> data> right.maxVal && left.isHeap && right.isHeap){
        Valid temp;
        temp.maxVal= root-> data;
        temp.isHeap= true;
        return temp;
    }
    else {
        Valid temp;
        temp.maxVal= max(root-> data, max(left.maxVal, right.maxVal));
        temp.isHeap= false;
        return temp;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Check Max Heap
 */
int main(){

}
