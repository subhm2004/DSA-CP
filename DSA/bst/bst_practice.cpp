/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_practice.cpp
 * PROBLEM  : Bst Practice
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST PRACTICE — Insert, search, delete, validate, LCA, kth, DLL convert
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST ke saare core operations ek file me practice.
//
// Operations: insert, search, min/max, predecessor/successor, delete,
//             validate BST, LCA, kth smallest, BST→DLL
// Complexity: Mostly O(h) per operation
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this-> data= data;
        this-> left= NULL;
        this-> right= NULL;
    }
};

// ── InsertInBST: recursive insert ──
Node* InsertInBST(Node* root,int data){
    if(root== NULL){
        root = new Node(data);
        return root;
    }
    else if(root-> data > data){
        root-> left= InsertInBST(root-> left, data);
    }
    else {
        root-> right= InsertInBST(root-> right, data);
    }
    return root;
}

// ── inorder: sorted traversal ──
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout << root-> data << " ";
    inorder(root-> right);
}

// ── takingInput: -1 tak insert (root by reference) ──
void takingInput(Node* &root){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root= InsertInBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}

// ── levelorder: BFS level-wise ──
void levelorder(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< " ";
            if(newnode-> left!= NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
        else {
            cout<< endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}

// ── searchtree: target node dhundho ──
Node* searchtree(Node* root, int& target){
    if(root== NULL){
        return NULL;
    }
    if(root-> data== target){
        return root;
    }
    else if(root-> data> target){
        return searchtree(root-> left, target);
    }
    else {
        return searchtree(root-> right, target);
    }
}

// ── FindMin: leftmost value ──
int FindMin(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root->left!= NULL){
        root= root-> left;
    }
    return root-> data;
}

// ── FindMax: rightmost value ──
int FindMax(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> right!= NULL){
        root= root-> right;
    }
    return root-> data;
}

// ── inorderpredecessor: node se chhota sabse bada ──
//   1) Node dhundho
//   2) Left subtree ka max = predecessor
int inorderpredecessor(Node* root, int target){
    Node* found= searchtree(root, target);
    int ans= -1;
    if(found!= NULL){
        ans= FindMax(found-> left);
    }
    return ans;
}

// ── inordersucessor: node se bada sabse chhota ──
int inordersucessor(Node* root, int target){
    Node* found= searchtree(root, target);
    int ans= -1;
    if(found!= NULL){
        ans= FindMin(found-> right);
    }
    return ans;
}

// ── deletioninBST: 3-case delete ──
//   1) 0 child → delete, NULL
//   2) 1 child → child return
//   3) 2 child → predecessor se replace
Node* deletioninBST(Node* root, int target){
    if(root== NULL){
        return NULL;
    }
    if(root-> data== target){
        if(root-> left== NULL && root-> right== NULL){
            delete root;
            return NULL;
        }
        else if(root-> left!= NULL && root-> right== NULL){
            Node* child= root-> left;
            return child;
        }
        else if(root-> right!= NULL && root-> left== NULL){
            Node* child= root-> right;
            return child;
        }
        else {
            int value = inorderpredecessor(root, target);
            root -> data= value;
            root-> left = deletioninBST(root-> left, value);
            return root;
        }
    }
    else if(root-> data< target){
        root-> right= deletioninBST(root-> right, target);
    }
    else {
        root-> left= deletioninBST(root-> left, target);
    }
    return root;
}

// ── validateBST: poora tree valid BST? ──
//   1) NULL → true
//   2) Leaf → true
//   3) Ek/two child — min/max range check
bool validateBST(Node* root){
    if(root== NULL){
        return true;
    }
    if(root-> left== NULL && root-> right== NULL){
        return true;
    }
    else if(root-> left!= NULL && root-> right== NULL){
        if(FindMax(root-> left) < root-> data){
            return validateBST(root-> left);
        }
    }
    else if(root-> right!= NULL && root-> left== NULL){
        if(FindMin(root-> right)> root-> data){
            return validateBST(root-> right);
        }
    }
    else {
        if((FindMax(root-> left) < root-> data)&& (FindMin(root-> right)> root-> data)){
            return (validateBST(root-> left) && validateBST(root-> right));
        }
    }
    return false;
}

// ── LCABST: BST property se LCA ──
Node* LCABST(Node* root, Node* p, Node* q){
    if(root== NULL){
        return NULL;
    }
    if(root== p){
        return p;
    }
    if(root== q){
        return q;
    }
    if(root!= p && root!= q){
        if((p-> data< root-> data && q-> data> root-> data)|| (p-> data> root-> data && q-> data< root-> data)){
            return root;
        }
        else if(p-> data< root-> data && q-> data< root-> data){
            return LCABST(root-> left, p,q);
        }
        else {
            return LCABST(root-> right, p, q);
        }
    }
}

// ── kthsmallest: inorder me k-- karke dhundho ──
//   1) Left recurse — mila to return
//   2) Root pe k--, k==0 → answer
//   3) Right recurse
int kthsmallest(Node* root, int k){
    if(root== NULL){
        return -1;
    }
        int left= kthsmallest(root-> left, k);
        if(left!= -1){
            return left;
        }
    k--;
    if(k==0){
        return root-> data;
    }
        int right= kthsmallest(root-> right, k);
        return right;
}

// ── printLL: DLL forward print ──
void printLL(Node* &head){
    if(head== NULL){
        return;
    }
    Node* temp= head;
    while(temp!= NULL){
        cout<< temp-> data<< "->";
        temp= temp-> right;
    }
}

// ── conversiontoDLL: reverse inorder flatten ──
void conversiontoDLL(Node* root, Node* &head){
    if(root== NULL){
        return;
    }
    conversiontoDLL(root-> right, head);
    root-> right= head;
    if(head!= NULL){
        head-> left= root;
    }
    head= root;
    conversiontoDLL(root-> left, head);
}

// ── main: BST validate demo ──
int main(){
    Node* root= NULL;
    Node* head= NULL;
    takingInput(root);
    cout<< "level order traversal is: "<< endl;
    levelorder(root);
    bool ans= validateBST(root);
    cout<< ans<< endl;
}
