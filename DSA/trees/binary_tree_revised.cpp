/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_revised.cpp
 * PROBLEM  : Binary Tree Revised
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <map>
using namespace std;

class Node{
  public:
	int data;
	Node* left;
	Node* right;

	Node(int val) {
	  this->data = val;
	  this->left = NULL;
	  this->right = NULL;
	}
};



/*
 * levelOrderTraversal()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void levelOrderTraversal(Node* root) {
	queue<Node*> q;
	q.push(root);
	q.push(NULL);


	while(!q.empty()) {
		Node* front = q.front();
		q.pop();

		if(front == NULL) {
			cout << endl;
			if(!q.empty()) {
				q.push(NULL);
			}
		}
		else {
			cout << front->data << " ";

			if(front->left != NULL) {
				q.push(front->left);
			}
			if(front->right != NULL) {
				q.push(front->right);
			}
		}
	}
}



/*
 * searchInorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : int inorder[], int size, int target
 * Returns : int
 */
int searchInorder(int inorder[], int size, int target){
  // Iterate over all elements
  for(int i=0; i<size; i++) {
    if(inorder[i] == target) {
      return i;
    }
  }
  return -1;
}



/*
 * createMapping()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : int inorder[], int size, map<int,int> &valueToIndexMap
 * Returns : void
 */
void createMapping(int inorder[], int size, map<int,int> &valueToIndexMap) {

    // Iterate over all elements
    for(int i=0; i<size; i++) {
      int element = inorder[i];
      int index = i;
      valueToIndexMap[element] = index;
    }

}



/*
 * constructTreeFromPreAndInorderTraversal()
 * Purpose : Tree DFS in specific visit order.
 * Params  : map<int,int> &valueToIndexMap, int preOrder[], int inOrder[], int &preIndex, int inOrderStart, int inOrderEnd, int size
 * Returns : Node*
 */
Node* constructTreeFromPreAndInorderTraversal( map<int,int> &valueToIndexMap, int preOrder[], int inOrder[], int &preIndex, int inOrderStart, int inOrderEnd, int size) {
  if(preIndex >= size || inOrderStart > inOrderEnd) {
    return NULL;
  }

  int element = preOrder[preIndex];
  preIndex++;
  Node* root = new Node(element);
  int position = valueToIndexMap[element];
  root->left = constructTreeFromPreAndInorderTraversal(valueToIndexMap,preOrder, inOrder, preIndex, inOrderStart, position-1, size);

  root->right = constructTreeFromPreAndInorderTraversal(valueToIndexMap,preOrder, inOrder, preIndex, position+1, inOrderEnd, size);

  return root;

}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Tree Revised
 */
int main(){
    int inorder[] = {10,8,6,2,4,12};
  int preOrder[] = {2,8,10,6,4,12};
  int size = 6;
  int preOrderIndex = 0;
  int inorderStart = 0;
  int inorderEnd = 5;
  map<int,int> valueToIndexMap;
  createMapping(inorder, size, valueToIndexMap);

  Node* root = constructTreeFromPreAndInorderTraversal(valueToIndexMap,preOrder, inorder, preOrderIndex, inorderStart,inorderEnd, size);
  levelOrderTraversal(root);
  return 0;
}
