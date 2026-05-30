/*
 * ============================================================================
 * TOPIC    : Trees — Serialize & Deserialize Binary Tree
 * FILE     : serialize_deserialize_binary_tree.cpp
 * PROBLEM  : Encode tree to string and decode back
 * LEETCODE : 297 — Serialize and Deserialize Binary Tree
 * APPROACH : Preorder with "null" markers, comma-separated
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    string serialize(TreeNode *root) {
        string out;
        dfsSer(root, out);
        return out;
    }

    TreeNode *deserialize(string data) {
        int i = 0;
        return dfsDes(data, i);
    }

private:
    void dfsSer(TreeNode *node, string &out) {
        if (!node) {
            out += "#,";
            return;
        }
        out += to_string(node->val) + ",";
        dfsSer(node->left, out);
        dfsSer(node->right, out);
    }

    TreeNode *dfsDes(const string &s, int &i) {
        if (s[i] == '#') {
            i += 2;
            return nullptr;
        }
        int j = i;
        while (s[j] != ',') j++;
        int val = stoi(s.substr(i, j - i));
        i = j + 1;
        TreeNode *node = new TreeNode(val);
        node->left = dfsDes(s, i);
        node->right = dfsDes(s, i);
        return node;
    }
};

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec c;
    string s = c.serialize(root);
    TreeNode *back = c.deserialize(s);
    cout << (back && back->val == 1 && back->right->left->val == 4 ? "OK" : "FAIL") << endl;
    return 0;
}
