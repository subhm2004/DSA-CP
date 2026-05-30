/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : validate_heap_from_cbt.cpp
 * PROBLEM  : Validate Heap From Cbt
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;
class Node{
    public:
    int data;
    Node* left;
    Node* right;
};
class Valid{
    public:
    int maxVal;
    bool IsHeap;
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
        temp.IsHeap= true;
        return temp;
    }
    if(root-> left== NULL && root-> right== NULL){
        Valid temp;
        temp.maxVal= root-> data;
        temp.IsHeap= true;
        return temp;
    }
    Valid left= CheckMaxHeap(root-> left);
    Valid right= CheckMaxHeap(root-> right);
    if(root-> data> left.maxVal && root-> data> right.maxVal && left.IsHeap && right.IsHeap){
        Valid temp;
        temp.maxVal= root-> data;
        temp.IsHeap= true;
        return temp;
    }
    else {
        Valid temp;
        temp.maxVal= max(root-> data, max(left.maxVal, right.maxVal));
        temp.IsHeap= false;
        return temp;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Validate Heap From Cbt
 */
int main(){
    Node* root= NULL;
}
