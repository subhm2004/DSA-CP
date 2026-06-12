#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LI CHAO SEGMENT TREE (Dynamic Convex Hull Trick on Segment)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM TYPE:
 *   Bahut saari lines hain: y = m*x + c
 *   Query: fixed x par sab lines me se MINIMUM (ya MAXIMUM) y kya hai?
 *
 * Example:
 *   Line 1: y = 2x + 1   → x=3 par y=7
 *   Line 2: y = -x + 10  → x=3 par y=7
 *   Line 3: y = 0x + 5   → x=3 par y=5  ← minimum
 *
 * Kyun Segment Tree?
 *   Classic CHT sirf monotonic slopes/inserts ke liye O(n) hota hai.
 *   Li Chao arbitrary order me lines insert + point query O(log X) deta hai.
 *   X = x ki range (coordinate compressed ya fixed [X_MIN, X_MAX]).
 *
 * NODE IDEA:
 *   Har node ek segment [l,r] cover karta hai aur us par "best line" store karta hai.
 *   Nayi line insert karte waqt midpoint par dono lines compare → jeeti wali node me,
 *   haari wali ko left/right child me push karo (recursively).
 *
 * Time: insert O(log X) | query O(log X)
 * Space: O(nodes) ≈ O(X * log X) worst case, dynamic nodes on demand
 * ════════════════════════════════════════════════════════════════════════════
 */

struct Line {
    long long m, c;  // y = m*x + c

    Line(long long _m = 0, long long _c = LLONG_MAX / 4) : m(_m), c(_c) {}

    long long eval(long long x) const {
        return m * x + c;
    }
};

class LiChaoTree {
private:
    struct Node {
        Line line;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    Node* root = nullptr;
    long long X_MIN, X_MAX;
    bool maximize;  // false = minimum query (default), true = maximum

    bool better(const Line& a, const Line& b, long long x) const {
        long long va = a.eval(x), vb = b.eval(x);
        return maximize ? (va > vb) : (va < vb);
    }

    /*
     * addLine(node, l, r, newLine)
     * ---------------------------
     * [l,r] segment par newLine insert karo.
     *
     * Mid = (l+r)/2 par current best vs newLine compare:
     *   - jeeti line node me rehti hai
     *   - haari line us side child me jati hai jahan wo mid ke baad better ho sakti hai
     *
     * Yeh "swap and recurse" trick Li Chao ka core hai.
     */
    void addLine(Node*& node, long long l, long long r, Line nw) {
        if (!node) {
            node = new Node();
            node->line = nw;
            return;
        }
        long long mid = (l + r) >> 1;

        Line cur = node->line;
        bool curBetterAtMid = better(cur, nw, mid);
        if (!curBetterAtMid) swap(cur, nw);
        node->line = cur;

        if (l == r) return;

        if (better(nw, cur, l))
            addLine(node->left, l, mid, nw);
        if (better(nw, cur, r))
            addLine(node->right, mid + 1, r, nw);
    }

    /*
     * query(node, l, r, x)
     * --------------------
     * Point x par best line ka value.
     * Root se leaf tak jaate hue har node ki line evaluate karo, best pick karo.
     */
    long long query(Node* node, long long l, long long r, long long x) const {
        if (!node) return maximize ? LLONG_MIN / 4 : LLONG_MAX / 4;
        long long best = node->line.eval(x);
        if (l == r) return best;
        long long mid = (l + r) >> 1;
        if (x <= mid)
            best = maximize ? max(best, query(node->left, l, mid, x))
                            : min(best, query(node->left, l, mid, x));
        else
            best = maximize ? max(best, query(node->right, mid + 1, r, x))
                            : min(best, query(node->right, mid + 1, r, x));
        return best;
    }

public:
  LiChaoTree(long long xMin, long long xMax, bool maxQuery = false)
        : X_MIN(xMin), X_MAX(xMax), maximize(maxQuery) {}

    void addLine(long long m, long long c) {
        addLine(root, X_MIN, X_MAX, Line(m, c));
    }

    long long query(long long x) const {
        assert(x >= X_MIN && x <= X_MAX);
        return query(root, X_MIN, X_MAX, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Lines: y = 2x+1, y = -x+10, y = 5 (horizontal)
    LiChaoTree lct(0, 1'000'000);

    lct.addLine(2, 1);
    lct.addLine(-1, 10);
    lct.addLine(0, 5);

  cout << "Li Chao — minimum y at x:\n";
    for (int x : {0, 1, 3, 5, 10})
        cout << "  x=" << x << " -> min y = " << lct.query(x) << "\n";

    // Classic CP use: taxi / hotel problem style
    // cost at position x from line (m,c) where m = -2*x0, c = cost + x0^2
    cout << "\nTaxi style: min cost to reach x=7\n";
    LiChaoTree taxi(0, 100);
    taxi.addLine(-2 * 0, 0 + 0LL * 0);   // start at 0, cost 0
    taxi.addLine(-2 * 3, 5 + 3LL * 3);   // start at 3, cost 5
    taxi.addLine(-2 * 8, 2 + 8LL * 8);   // start at 8, cost 2
    cout << "  min cost at x=7 -> " << taxi.query(7) << "\n";

    return 0;
}
