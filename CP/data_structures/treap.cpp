/*
 * ============================================================================
 * TOPIC    : Data Structures — Treap
 * FILE     : treap.cpp
 * PROBLEM  : BST + heap priority — insert/erase/kth order O(log n)
 * APPROACH : Randomized treap with split/merge; implicit treap for arrays
 * COMPLEX  : O(log n) expected per operation
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// ── Key treap (ordered set / map by key) ────────────────────────────────────
struct KeyTreap {
    struct Node {
        int key, pr, sz;
        Node *l = nullptr, *r = nullptr;
        Node(int k) : key(k), pr((int)rng()), sz(1) {}
    };
    Node *root = nullptr;

    int getSize(Node *t) { return t ? t->sz : 0; }
    void upd(Node *t) {
        if (t) t->sz = 1 + getSize(t->l) + getSize(t->r);
    }

    void split(Node *t, int key, Node *&a, Node *&b) { // a: < key, b: >= key
        if (!t) {
            a = b = nullptr;
            return;
        }
        if (t->key < key) {
            split(t->r, key, t->r, b);
            a = t;
        } else {
            split(t->l, key, a, t->l);
            b = t;
        }
        upd(t);
    }

    Node *merge(Node *a, Node *b) {
        if (!a || !b) return a ? a : b;
        if (a->pr > b->pr) {
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }

    void insert(int key) {
        Node *a, *b, *c;
        split(root, key, a, b);
        split(b, key + 1, b, c);
        if (!b)
            root = merge(merge(a, new Node(key)), c);
        else
            root = merge(merge(a, b), c);
    }

    void erase(int key) {
        Node *a, *b, *c;
        split(root, key, a, b);
        split(b, key + 1, b, c);
        delete b;
        root = merge(a, c);
    }

    bool contains(int key) {
        Node *cur = root;
        while (cur) {
            if (key == cur->key) return true;
            cur = key < cur->key ? cur->l : cur->r;
        }
        return false;
    }

    int kth(int k) { // 1-indexed
        Node *cur = root;
        while (cur) {
            int left = getSize(cur->l);
            if (k == left + 1) return cur->key;
            if (k <= left) cur = cur->l;
            else {
                k -= left + 1;
                cur = cur->r;
            }
        }
        return -1;
    }
};

// ── Implicit treap (sequence: reverse range, insert, erase by index) ─────────
struct ImplicitTreap {
    struct Node {
        int pr, sz;
        char val;
        bool rev = false;
        Node *l = nullptr, *r = nullptr;
        Node(char v) : pr((int)rng()), sz(1), val(v) {}
    };
    Node *root = nullptr;

    int getSize(Node *t) { return t ? t->sz : 0; }
    void push(Node *t) {
        if (!t || !t->rev) return;
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
    }
    void upd(Node *t) {
        if (t) t->sz = 1 + getSize(t->l) + getSize(t->r);
    }

    void split(Node *t, int k, Node *&a, Node *&b) { // first k nodes → a
        push(t);
        if (!t) {
            a = b = nullptr;
            return;
        }
        int left = getSize(t->l);
        if (k <= left) {
            split(t->l, k, a, t->l);
            b = t;
        } else {
            split(t->r, k - left - 1, t->r, b);
            a = t;
        }
        upd(t);
    }

    Node *merge(Node *a, Node *b) {
        push(a);
        push(b);
        if (!a || !b) return a ? a : b;
        if (a->pr > b->pr) {
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }

    void insert(int pos, char c) {
        Node *a, *b;
        split(root, pos, a, b);
        root = merge(merge(a, new Node(c)), b);
    }

    void reverse(int l, int r) { // 0-indexed [l, r)
        Node *a, *b, *c;
        split(root, r, b, c);
        split(b, l, a, b);
        if (b) b->rev ^= 1;
        root = merge(merge(a, b), c);
    }

    string inorder(Node *t) {
        if (!t) return "";
        push(t);
        return inorder(t->l) + t->val + inorder(t->r);
    }

    string getString() { return inorder(root); }
};

int main() {
    KeyTreap kt;
    for (int x : {5, 3, 7, 1, 9}) kt.insert(x);
    cout << "contains 7: " << kt.contains(7) << endl;
    cout << "3rd smallest: " << kt.kth(3) << endl;

    ImplicitTreap it;
    string s = "abcdef";
    for (char c : s) it.insert((int)it.getString().size(), c);
    it.reverse(1, 4); // reverse "bcd" → "dcb"
    cout << it.getString() << endl; // adcbef
    return 0;
}
