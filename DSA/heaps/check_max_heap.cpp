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

// ════════════════════════════════════════════════════════════════════════════
// CHECK MAX HEAP — Tree representation validate karo
// ────────────────────────────────────────────────────────────────────────────
// Har node apne subtrees ke sabse bade se bada hona chahiye
// DFS post-order: left/right se (maxVal, isHeap) lao
// Root property fail -> isHeap=false return
// Same logic as validate_heap_from_cbt.cpp (naming alag)
// ════════════════════════════════════════════════════════════════════════════

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

// ── CheckMaxHeap: recursive max-heap validation ────────────────────────────
//   1) NULL node -> valid, maxVal=INT_MIN
//   2) leaf -> valid, maxVal=node data
//   3) left/right subtrees check — dono valid aur root sabse bada
//   4) fail pe isHeap=false, maxVal=max of subtree values
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

// ── main: empty stub ─────────────────────────────────────────────────────────
int main(){

}
