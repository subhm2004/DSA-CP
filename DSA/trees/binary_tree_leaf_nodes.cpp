/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_leaf_nodes.cpp
 * PROBLEM  : Binary Tree Leaf Nodes
 * LEETCODE : 404 — Sum of Left Leaves
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
// FIND LEAVES — Bottom-up height se leaves group karo
// ────────────────────────────────────────────────────────────────────────────
// Problem: Leaves ko unki "height from bottom" ke hisaab se group karo.
//          (Leetcode 366 — Find Leaves of Binary Tree)
//
// Approach: Post-order DFS
//   - Height = max(leftH, rightH) + 1
//   - Leaf height = 0 → result[0] me daalo
//
// Complexity: Time O(n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── buildTree: level-order array se tree ──
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

// ── printTree: level-order print (null bhi) ──
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
            cout << current->val << " ";
        else
            cout << "null ";

        if (current)
        {
            q.push(current->left);
            q.push(current->right);
        }
    }
    cout << endl;
}

class Solution
{
public:
    // ── findLeaves: public API — leaves by bottom-up height ──
    //   1) Empty result vector
    //   2) traverse() se height-wise collect
    //   3) result return
    vector<vector<int>> findLeaves(TreeNode *root)
    {
        vector<vector<int>> result;
        traverse(root, result);
        return result;
    }

private:
    // ── traverse: post-order height nikalo, leaf bucket me daalo ──
    //   1) NULL → height -1
    //   2) Left/right height lo
    //   3) currentHeight = max + 1
    //   4) result[currentHeight] me val push
    //   5) Height return (parent ke liye)
    int traverse(TreeNode *node, vector<vector<int>> &result)
    {
        if (!node)
            return -1;

        int leftHeight = traverse(node->left, result);
        int rightHeight = traverse(node->right, result);
        int currentHeight = max(leftHeight, rightHeight) + 1;

        if (currentHeight >= result.size())
            result.resize(currentHeight + 1);

        result[currentHeight].push_back(node->val);

        return currentHeight;
    }
};

// ── printResult: grouped leaves print ──
void printResult(const vector<vector<int>> &result)
{
    for (const auto &level : result)
    {
        cout << "[ ";
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << "]\n";
    }
}

// ── main: demo ──
int main()
{
    vector<int> values = {1, 2, 3, 4, 5, -1, -1};
    TreeNode *root = buildTree(values);

    cout << "Level-order tree: ";
    printTree(root);

    Solution sol;
    vector<vector<int>> result = sol.findLeaves(root);

    cout << "Leaves by level:\n";
    printResult(result);

    return 0;
}
