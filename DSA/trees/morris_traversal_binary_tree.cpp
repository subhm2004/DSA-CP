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

// ════════════════════════════════════════════════════════════════════════════
// MORRIS TRAVERSAL — O(1) space inorder traversal
// ────────────────────────────────────────────────────────────────────────────
// Problem: Stack/recursion ke bina inorder traversal karo.
//
// Approach: Threaded binary tree trick
//   - Left subtree ka inorder predecessor dhundho
//   - Predecessor->right = current (thread banao)
//   - Visit ke baad thread hatao
//
// Complexity: Time O(n)  |  Space O(1) extra
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── buildTree: level-order array se tree banao ──
//   1) -1 ya empty → nullptr
//   2) BFS queue se left/right assign
//   3) Index i array me aage badhao
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

// ── morrisTraversal: O(1) space inorder ──
//   1) current pointer root se start
//   2) Left nahi → print + right jao
//   3) Left hai → predecessor dhundho (rightmost in left subtree)
//   4) Thread nahi → predecessor->right = current, left jao
//   5) Thread hai → thread hatao, print, right jao
void morrisTraversal(TreeNode *root)
{
    TreeNode *current = root;

    while (current != nullptr)
    {
        if (current->left == nullptr)
        {
            cout << current->val << " ";  // visit
            current = current->right;
        }
        else
        {
            TreeNode *predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current)
                predecessor = predecessor->right;  // inorder predecessor

            if (predecessor->right == nullptr)
            {
                predecessor->right = current;  // thread banao
                current = current->left;
            }
            else
            {
                predecessor->right = nullptr;  // thread hatao
                cout << current->val << " ";
                current = current->right;
            }
        }
    }
}

// ── main: Morris inorder demo ──
int main()
{
    vector<int> values = {1, 2, 3, -1, 5, -1, 4}; // -1 means NULL
    TreeNode *root = buildTree(values);

    cout << "Morris Inorder Traversal: ";
    morrisTraversal(root);
    cout << endl;

    return 0;
}
