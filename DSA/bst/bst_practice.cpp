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


/*
 * InsertInBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int data
 * Returns : Node*
 */
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


/*
 * inorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root
 * Returns : void
 */
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout << root-> data << " ";
    inorder(root-> right);
}
void takingInput(Node* &root){  // root must be passed by reference
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root= InsertInBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}


/*
 * levelorder()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : void
 */
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


/*
 * searchtree()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, int& target
 * Returns : Node*
 */
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


/*
 * FindMin()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : int
 */
int FindMin(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root->left!= NULL){
        root= root-> left;
    }
    return root-> data;
}


/*
 * FindMax()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : int
 */
int FindMax(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> right!= NULL){
        root= root-> right;
    }
    return root-> data;
}


/*
 * inorderpredecessor()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root, int target
 * Returns : int
 */
int inorderpredecessor(Node* root, int target){
    Node* found= searchtree(root, target);
    int ans= -1;
    if(found!= NULL){
        ans= FindMax(found-> left);
    }
    return ans;
}


/*
 * inordersucessor()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root, int target
 * Returns : int
 */
int inordersucessor(Node* root, int target){
    Node* found= searchtree(root, target);
    int ans= -1;
    if(found!= NULL){
        ans= FindMin(found-> right);
    }
    return ans;
}


/*
 * deletioninBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int target
 * Returns : Node*
 */
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


/*
 * validateBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root
 * Returns : bool
 */
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


/*
 * LCABST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, Node* p, Node* q
 * Returns : Node*
 */
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


/*
 * kthsmallest()
 * Purpose : Min heap or quickselect for k-th statistic.
 * Params  : Node* root, int k
 * Returns : int
 */
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


/*
 * printLL()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* &head
 * Returns : void
 */
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


/*
 * conversiontoDLL()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, Node* &head
 * Returns : void
 */
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



/*
 * main()
 * Purpose : Entry point — demo/test for Bst Practice
 */
int main(){
    Node* root= NULL;
    Node* head= NULL;
    takingInput(root);
    cout<< "level order traversal is: "<< endl;
    levelorder(root);
    bool ans= validateBST(root);
    cout<< ans<< endl;
}
