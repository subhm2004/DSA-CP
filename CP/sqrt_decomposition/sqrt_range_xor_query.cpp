/*
 * ============================================================================
 * TOPIC    : Square Root Decomposition
 * FILE     : sqrt_range_xor_query.cpp
 * PROBLEM  : Range XOR query + point update
 * APPROACH : Blocks of size sqrt(n) — blockXor precompute (sum jaisa, ^ use karo)
 * COMPLEX  : Query O(sqrt n)  |  Update O(1)  |  Build O(n)
 * ============================================================================
 *
 * XOR bhi associative hai (identity = 0), isliye range XOR sqrt se sum jaisa hi:
 *   blockXor[b] = block b ke saare elements ka XOR
 *   query [L,R] = left partial ^ full blocks ^ right partial
 *   update idx  = blockXor[b] ^= arr[idx] ^ newVal
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SQRT DECOMPOSITION — Range XOR Query + Point Update
// ────────────────────────────────────────────────────────────────────────────
// Sum sqrt me + hota hai, yahan ^ (XOR).
// Range XOR = prefixXOR(R) ^ prefixXOR(L-1) — BIT me bhi same idea.
//
// Params:
//   blockSize   -> ~sqrt(n)
//   blockXor[b] -> block b ka precomputed XOR
//
// Complexity: Build O(n) | Query O(sqrt n) | Update O(1)
// ════════════════════════════════════════════════════════════════════════════

class SqrtRangeXor {
private:
    vector<int> arr;
    vector<int> blockXor;
    int n;
    int blockSize;

public:
    // ── Constructor: array lo, blocks banao, har block ka XOR nikaalo ───────
    //   1) arr copy, blockSize ≈ sqrt(n)+1
    //   2) har element ko apne block ke blockXor me ^= karo
    //   3) ab full blocks query me O(1) combine ho jayenge
    SqrtRangeXor(const vector<int>& input) {
        arr = input;
        n = (int)arr.size();
        blockSize = (int)sqrt(n + 0.0) + 1;
        int numBlocks = (int)ceil((double)n / blockSize);
        blockXor.assign(numBlocks, 0);

        for (int i = 0; i < n; i++) {
            blockXor[i / blockSize] ^= arr[i];
        }
    }

    // ── query: range [left, right] ka XOR nikalo ───────────────────────────
    //   1) same block → left se right elements ^ karo
    //   2) alag blocks → left partial ^ middle blockXor ^ right partial
    //   3) XOR order matter nahi karta — associative + commutative
    int query(int left, int right) {
        int total = 0;

        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock) {
            for (int i = left; i <= right; i++) {
                total ^= arr[i];
            }
        } else {
            int leftEnd = (leftBlock + 1) * blockSize - 1;
            for (int i = left; i <= leftEnd; i++) {
                total ^= arr[i];
            }

            for (int b = leftBlock + 1; b <= rightBlock - 1; b++) {
                total ^= blockXor[b];
            }

            int rightStart = rightBlock * blockSize;
            for (int i = rightStart; i <= right; i++) {
                total ^= arr[i];
            }
        }

        return total;
    }

    // ── update: index idx ki value newValue se replace karo ────────────────
    //   1) blockXor me delta: purani ^ nayi value XOR karo
    //      (purani hatao + nayi add = arr[idx] ^ newValue)
    //   2) arr[idx] = newValue — O(1) point update
    void update(int idx, int newValue) {
        int block = idx / blockSize;
        blockXor[block] ^= arr[idx] ^ newValue;
        arr[idx] = newValue;
    }

    // ── printState: debug — array + block XOR print ─────────────────────────
    void printState() {
        cout << "Array: ";
        for (int x : arr) {
            cout << x << " ";
        }
        cout << "\nBlock size: " << blockSize << "\n";
        cout << "Block XOR: ";
        for (int x : blockXor) {
            cout << x << " ";
        }
        cout << "\n";
    }
};

int main() {
    // Demo: {1,2,3,4,5,6,7,8}
    // XOR(0,3) = 1^2^3^4 = 4
    // update(2,10) -> arr[2]=10, XOR(0,3) = 1^2^10^4 = 13
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    SqrtRangeXor st(a);

    cout << "=== Sqrt Range XOR ===\n";
    st.printState();

    cout << "\nInitial queries:\n";
    cout << "XOR(0, 3) = " << st.query(0, 3) << "\n"; // 1^2^3^4 = 4
    cout << "XOR(2, 6) = " << st.query(2, 6) << "\n"; // 3^4^5^6^7 = 3
    cout << "XOR(0, 7) = " << st.query(0, 7) << "\n"; // full array xor

    cout << "\nUpdate arr[2] = 10\n";
    st.update(2, 10);

    cout << "After update:\n";
    cout << "XOR(0, 3) = " << st.query(0, 3) << "\n"; // 1^2^10^4 = 13
    cout << "XOR(2, 6) = " << st.query(2, 6) << "\n"; // 10^4^5^6^7 = 10

    return 0;
}
