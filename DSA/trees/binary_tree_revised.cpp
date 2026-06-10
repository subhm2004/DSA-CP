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

// ════════════════════════════════════════════════════════════════════════════
// BUILD TREE (REVISED) — Preorder+Inorder with hashmap optimization
// ────────────────────────────────────────────────────────────────────────────
// Problem: Preorder + Inorder se tree banao — O(n) with value→index map.
//
// Approach: Hashmap se O(1) inorder search
// Complexity: Time O(n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

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

// ── levelOrderTraversal: BFS level-wise print ──
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

// ── searchInorder: linear search (backup — map preferred) ──
int searchInorder(int inorder[], int size, int target){
  for(int i=0; i<size; i++) {
    if(inorder[i] == target) {
      return i;
    }
  }
  return -1;
}

// ── createMapping: value → inorder index hashmap ──
//   1) Har inorder element ke liye map[val] = index
//   2) O(1) lookup build step me
void createMapping(int inorder[], int size, map<int,int> &valueToIndexMap) {
    for(int i=0; i<size; i++) {
      int element = inorder[i];
      int index = i;
      valueToIndexMap[element] = index;
    }
}

// ── constructTreeFromPreAndInorderTraversal: optimized build ──
//   1) Base: invalid range → NULL
//   2) preorder[preIndex] = root, preIndex++
//   3) Map se position = O(1)
//   4) Left = inorder[start..pos-1], Right = inorder[pos+1..end]
Node* constructTreeFromPreAndInorderTraversal( map<int,int> &valueToIndexMap, int preOrder[], int inOrder[], int &preIndex, int inOrderStart, int inOrderEnd, int size) {
  if(preIndex >= size || inOrderStart > inOrderEnd) {
    return NULL;
  }

  int element = preOrder[preIndex];
  preIndex++;
  Node* root = new Node(element);
  int position = valueToIndexMap[element];  // O(1) lookup
  root->left = constructTreeFromPreAndInorderTraversal(valueToIndexMap,preOrder, inOrder, preIndex, inOrderStart, position-1, size);

  root->right = constructTreeFromPreAndInorderTraversal(valueToIndexMap,preOrder, inOrder, preIndex, position+1, inOrderEnd, size);

  return root;
}

// ── main: map-based tree construction demo ──
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
