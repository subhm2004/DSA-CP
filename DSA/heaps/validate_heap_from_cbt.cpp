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

// ════════════════════════════════════════════════════════════════════════════
// VALIDATE MAX HEAP (TREE) — Recursive DFS se check
// ────────────────────────────────────────────────────────────────────────────
// Max heap: har node >= dono children ke max
// Post-order: left/right se maxVal aur IsHeap lao
// Root bada hona chahiye dono subtrees ke max se
// Valid struct: maxVal (subtree max) + IsHeap flag
// ════════════════════════════════════════════════════════════════════════════

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

// ── CheckMaxHeap: tree max-heap hai ya nahi ───────────────────────────────
//   1) NULL -> maxVal=INT_MIN, IsHeap=true (base case)
//   2) leaf -> maxVal=data, IsHeap=true
//   3) left/right recursively check karo
//   4) root > left.maxVal && root > right.maxVal && dono subtrees valid -> true
//   5) warna IsHeap=false, maxVal update karke return
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

// ── main: stub — root NULL se demo ───────────────────────────────────────────
int main(){
    Node* root= NULL;
}
