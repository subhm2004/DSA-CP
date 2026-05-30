/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : construct_bst.cpp
 * PROBLEM  : Construct Bst
 * LEETCODE : 1008 — Construct Binary Search Tree from Preorder Traversal
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *insertBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}

TreeNode *buildBST(const vector<int> &values)
{
    TreeNode *root = nullptr;
    for (int val : values)
    {
        if (val != -1) // Ignore -1 as it represents NULL in input
            root = insertBST(root, val);
    }
    return root;
}



/*
 * inorderTraversal()
 * Purpose : Tree DFS in specific visit order.
 * Params  : TreeNode *root
 * Returns : void
 */
void inorderTraversal(TreeNode *root)
{
    if (!root)
        return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}



/*
 * main()
 * Purpose : Entry point — demo/test for Construct Bst
 */
int main()
{
    vector<int> values = {5, 3, 7, 2, 4, 6, 8}; // BST values
    TreeNode *root = buildBST(values);

    cout << "Inorder Traversal (Sorted BST): ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
