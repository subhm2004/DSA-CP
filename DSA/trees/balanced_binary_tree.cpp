/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : balanced_binary_tree.cpp
 * PROBLEM  : Balanced Binary Tree
 * LEETCODE : 110 — Balanced Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <cmath>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *CreateTree()
{
    int val;
    cout << "Enter data (-1 for NULL): ";
    cin >> val;
    if (val == -1)
    {
        return NULL;
    }
    Node *root = new Node(val);
    root->left = CreateTree();
    root->right = CreateTree();
    return root; // Missing return statement fixed
}



/*
 * maximumDepth()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node *root
 * Returns : int
 */
int maximumDepth(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = maximumDepth(root->left);
    int right = maximumDepth(root->right);
    return max(left, right) + 1;
}



/*
 * isBalanced()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node *root
 * Returns : bool
 */
bool isBalanced(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    int left = maximumDepth(root->left);
    int right = maximumDepth(root->right);
    bool difference = (abs(left - right) <= 1);
    bool lsubtree = isBalanced(root->left);
    bool rsubtree = isBalanced(root->right);
    return difference && lsubtree && rsubtree;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Balanced Binary Tree
 */
int main()
{
    Node *root = CreateTree();
    if (isBalanced(root))
    {
        cout << "The tree is height balanced." << endl;
    }
    else
    {
        cout << "The tree is NOT height balanced." << endl;
    }
    return 0;
}
