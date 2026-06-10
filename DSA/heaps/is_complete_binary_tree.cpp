/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : is_complete_binary_tree.cpp
 * PROBLEM  : Is Complete Binary Tree
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : priority_queue for O(log n) min/max access.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COMPLETE BINARY TREE (CBT) CHECK — Level order se verify karo
// ────────────────────────────────────────────────────────────────────────────
// CBT = last level left-filled, NULL ke baad koi node nahi
// Level order me NULL aane ke baad agar non-NULL dikhe -> not CBT
// Heap array representation ke liye CBT property zaroori hoti hai
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
};

// ── levelordertraversal: CBT property level-order se check ─────────────────
//   1) queue me root push, flag=false (NULL mila ya nahi)
//   2) non-NULL node -> agar pehle NULL mil chuka to false return
//   3) warna dono children queue me push karo
//   4) NULL node -> flag=true set karo (aage sab NULL hona chahiye)
//   5) end tak sab sahi -> true return
bool levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    bool flag = false;
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode== NULL){
            flag= true; // NULL mil gaya — ab sirf NULL aane chahiye
        }
        else {
            if(flag== true){
                return false; // NULL ke baad node mila -> CBT nahi
            }
            q.push(newnode-> left);
            q.push(newnode-> right);
        }
    }
    return true;
}

// ── CheckCBT: wrapper — CBT hai ya nahi ────────────────────────────────────
//   1) levelordertraversal() call karke result return karo
//   2) (Note: abhi return statement missing hai — demo stub)
bool CheckCBT(Node* root){
    levelordertraversal(root);


}
