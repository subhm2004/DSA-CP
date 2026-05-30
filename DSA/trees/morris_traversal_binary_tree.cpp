/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : morris_traversal_binary_tree.cpp
 * PROBLEM  : Morris Traversal Binary Tree
 * LEETCODE : 94 — Binary Tree Inorder Traversal (Morris O(1) space)
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Morris traversal — O(1) extra space via threading.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *buildTree(const vector<int> &values)
{
    if (values.empty() || values[0] == -1)
        return nullptr;

    TreeNode *root = new TreeNode(values[0]);
    queue<TreeNode *> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < values.size())
    {
        TreeNode *current = q.front();
        q.pop();

        if (values[i] != -1)
        {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != -1)
        {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
}



/*
 * morrisTraversal()
 * Purpose : Morris traversal — O(1) extra space via threading.
 * Params  : TreeNode *root
 * Returns : void
 */
void morrisTraversal(TreeNode *root)
{
    TreeNode *current = root;

    while (current != nullptr)
    {
        if (current->left == nullptr)
        {
            cout << current->val << " ";
            current = current->right;
        }
        else
        {
            TreeNode *predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current)
                predecessor = predecessor->right;

            if (predecessor->right == nullptr)
            {
                predecessor->right = current;
                current = current->left;
            }
            else
            {
                predecessor->right = nullptr;
                cout << current->val << " ";
                current = current->right;
            }
        }
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Morris Traversal Binary Tree
 */
int main()
{
    vector<int> values = {1, 2, 3, -1, 5, -1, 4}; // -1 means NULL
    TreeNode *root = buildTree(values);

    cout << "Morris Inorder Traversal: ";
    morrisTraversal(root);
    cout << endl;

    return 0;
}
