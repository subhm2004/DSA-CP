/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : make_binary_tree.cpp
 * PROBLEM  : Make Binary Tree
 * LEETCODE : 894 — All Possible Full Binary Trees
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MAKE BINARY TREE — Level-order array se tree construct
// ────────────────────────────────────────────────────────────────────────────
// Problem: Array representation (Leetcode style) se binary tree banao.
//          -1 = NULL node.
//
// Approach: BFS queue se parent-child link
// Complexity: Time O(n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── buildTree: array → binary tree ──
//   1) Empty/-1 → nullptr
//   2) Root banao, queue me daalo
//   3) Har node ke left/right assign karo
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

// ── printTree: level-order traversal print ──
void printTree(TreeNode *root)
{
    if (!root)
    {
        cout << "Tree is empty.\n";
        return;
    }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        if (current)
        {
            cout << current->val << " ";
            q.push(current->left);
            q.push(current->right);
        }
        else
        {
            cout << "Null ";
        }
    }
    cout << endl;
}

// ── main: build + print demo ──
int main()
{
    vector<int> values = {1, 2, 3, -1, 5, -1, 4};
    TreeNode *root = buildTree(values);

    cout << "Level Order Traversal: ";
    printTree(root);

    return 0;
}
