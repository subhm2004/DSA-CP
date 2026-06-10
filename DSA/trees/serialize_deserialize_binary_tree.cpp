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

// ════════════════════════════════════════════════════════════════════════════
// SERIALIZE / DESERIALIZE — Tree ↔ String conversion
// ────────────────────────────────────────────────────────────────────────────
// Problem: Binary tree ko string me encode karo aur wapas decode karo.
//
// Approach: Preorder DFS + "#" null marker
//   - Serialize: val,left,right preorder — null = "#,"
//   - Deserialize: same order se recursively tree rebuild
//
// Complexity: Time O(n)  |  Space O(n) string + recursion
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // ── serialize: tree → comma-separated preorder string ──
    //   1) Empty out string
    //   2) dfsSer preorder me "#" ya val append
    //   3) Final string return
    string serialize(TreeNode *root) {
        string out;
        dfsSer(root, out);
        return out;
    }

    // ── deserialize: string → tree rebuild ──
    //   1) Index i = 0 se start
    //   2) dfsDes recursively node banaye
    //   3) Root return
    TreeNode *deserialize(string data) {
        int i = 0;
        return dfsDes(data, i);
    }

private:
    // ── dfsSer: preorder serialize helper ──
    //   1) NULL → "#," append
    //   2) Warna val + "," then left, then right
    void dfsSer(TreeNode *node, string &out) {
        if (!node) {
            out += "#,";
            return;
        }
        out += to_string(node->val) + ",";
        dfsSer(node->left, out);
        dfsSer(node->right, out);
    }

    // ── dfsDes: preorder deserialize helper ──
    //   1) '#' → nullptr, i += 2 skip
    //   2) Number parse karo (comma tak)
    //   3) Node banao, left/right recursively
    TreeNode *dfsDes(const string &s, int &i) {
        if (s[i] == '#') {
            i += 2;  // "#," skip
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

// ── main: round-trip serialize/deserialize test ──
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
