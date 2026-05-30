// given 2 nodes p and q, you have to find the ancestor common to both the nodes
#include<iostream>
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

Node* CreateTree(){
    int val;
    cout<< "enter data"<< endl;
    cin>> val;
    if(val==-1){
        return NULL;
    }
    Node* root = new Node(val);
    root-> left= CreateTree();
    root-> right= CreateTree();
}
Node* leastcommonancestor(Node* root, Node* p, Node* q){
    if(root== NULL){
        return NULL;
    }
    if(root== p){
        return p;
    }
    if(root== q){
        return q;
    }
        Node* left= leastcommonancestor(root->left,p,q);
        Node* right= leastcommonancestor(root-> right,p,q);
        if(left!= NULL && right!= NULL){
            return root;
        }
        else if(left!= NULL && right== NULL){
            return left;
        }
        else if(left== NULL && right != NULL){
            return right;
        }
        else {
            return NULL;
        }

}
int main(){
    Node* root= CreateTree();
   
}