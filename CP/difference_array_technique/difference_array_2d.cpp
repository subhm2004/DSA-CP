/*
 * ============================================================================
 * TOPIC    : Difference Array Technique (2D)
 * FILE     : difference_array_2d.cpp
 * PROBLEM  : Submatrix [r1,c1]..[r2,c2] me batch update (+val ya *val)
 * APPROACH : 4 corners mark on diff, phir 2D prefix (sum ya product)
 * COMPLEX  : Update O(1) | Rebuild O(rows * cols)
 * ============================================================================
 *
 * DONO CLASSES — same 4-corner marking, alag rebuild:
 *
 *   DiffArray2DAdd      →  += val at corners  →  2D prefix SUM   →  mat += diff
 *   DiffArray2DMultiply →  *= val at corners  →  2D prefix PRODUCT →  mat *= diff
 *
 * 4 CORNERS (dono me same positions):
 *   diff[r1][c1]         op val
 *   diff[r1][c2 + 1]     op inv(val)   [multiply me]  ya  -= val [add me]
 *   diff[r2 + 1][c1]     op inv(val) / -= val
 *   diff[r2 + 1][c2 + 1] op val
 */

#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1'000'000'007LL;

long long modPow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long modInv(long long a) {
    return modPow(a, MOD - 2);
}

// ── printMatrix: debug helper ─────────────────────────────────────────────
void printMatrix(const vector<vector<long long>>& mat, const string& label) {
    cout << label << ":\n";
    for (auto& row : mat) {
        for (long long x : row) {
            cout << setw(4) << x << " ";
        }
        cout << "\n";
    }
}

// ════════════════════════════════════════════════════════════════════════════
// CLASS 1 — DiffArray2DAdd (ADDITIVE)
// ────────────────────────────────────────────────────────────────────────────
// Submatrix me +val:
//   diff init = 0
//   4 corners: += val / -= val
//   2D prefix SUM: diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1]
//   mat[i][j] += diff[i][j]
// ════════════════════════════════════════════════════════════════════════════

class DiffArray2DAdd {
private:
    int rows, cols;
    vector<vector<long long>> diff;

    // ── apply2DPrefixSum: marks → cumulative delta (additive) ───────────────
    void apply2DPrefixSum() {
        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j <= cols; j++) {
                if (i > 0) {
                    diff[i][j] += diff[i - 1][j];
                }
                if (j > 0) {
                    diff[i][j] += diff[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    diff[i][j] -= diff[i - 1][j - 1];
                }
            }
        }
    }

public:
    // ── DiffArray2DAdd: diff (rows+1)x(cols+1), sab 0 ────────────────────
    DiffArray2DAdd(int rows, int cols) : rows(rows), cols(cols) {
        diff.assign(rows + 1, vector<long long>(cols + 1, 0));
    }

    // ── rangeAdd: [r1,c1]..[r2,c2] me har cell me +val — O(1) ─────────────
    //   4 corners pe += / -= mark (poori submatrix walk nahi)
    void rangeAdd(int r1, int c1, int r2, int c2, long long val) {
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // ── buildFinalMatrix: prefix sum + base me add ─────────────────────────
    vector<vector<long long>> buildFinalMatrix(
        const vector<vector<long long>>& base) {
        apply2DPrefixSum();

        vector<vector<long long>> mat = base;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] += diff[i][j];
            }
        }
        return mat;
    }

    void printDiffMarks() const {
        cout << "Add marks (" << rows + 1 << "x" << cols + 1 << "):\n";
        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j <= cols; j++) {
                cout << setw(4) << diff[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

// ════════════════════════════════════════════════════════════════════════════
// CLASS 2 — DiffArray2DMultiply (MULTIPLICATIVE)
// ────────────────────────────────────────────────────────────────────────────
// Submatrix me *val (mod MOD):
//   diff init = 1  (multiply identity)
//   4 corners: *= val / *= val^-1
//   2D prefix PRODUCT:
//     diff[i][j] *= diff[i-1][j] * diff[i][j-1] * inv(diff[i-1][j-1])
//   mat[i][j] *= diff[i][j]
//
// Additive prefix SUM ka multiply version — inclusion-exclusion:
//   sum:  +a +b -overlap
//   prod: *a *b /overlap
// ════════════════════════════════════════════════════════════════════════════

class DiffArray2DMultiply {
private:
    int rows, cols;
    vector<vector<long long>> diff;

    // ── apply2DPrefixProduct: marks → cumulative multiplier ────────────────
    void apply2DPrefixProduct() {
        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j <= cols; j++) {
                if (i > 0) {
                    diff[i][j] = diff[i][j] * diff[i - 1][j] % MOD;
                }
                if (j > 0) {
                    diff[i][j] = diff[i][j] * diff[i][j - 1] % MOD;
                }
                if (i > 0 && j > 0) {
                    diff[i][j] = diff[i][j] * modInv(diff[i - 1][j - 1]) % MOD;
                }
            }
        }
    }

public:
    // ── DiffArray2DMultiply: diff (rows+1)x(cols+1), sab 1 ───────────────
    DiffArray2DMultiply(int rows, int cols) : rows(rows), cols(cols) {
        diff.assign(rows + 1, vector<long long>(cols + 1, 1));
    }

    // ── rangeMultiply: [r1,c1]..[r2,c2] me har cell me *val — O(1) ───────
    //   4 corners: *= val ya *= val^-1 (cancel ke liye)
    void rangeMultiply(int r1, int c1, int r2, int c2, long long val) {
        diff[r1][c1] = diff[r1][c1] * val % MOD;
        diff[r1][c2 + 1] = diff[r1][c2 + 1] * modInv(val) % MOD;
        diff[r2 + 1][c1] = diff[r2 + 1][c1] * modInv(val) % MOD;
        diff[r2 + 1][c2 + 1] = diff[r2 + 1][c2 + 1] * val % MOD;
    }

    // ── buildFinalMatrix: prefix product + base me multiply ───────────────
    vector<vector<long long>> buildFinalMatrix(
        const vector<vector<long long>>& base) {
        apply2DPrefixProduct();

        vector<vector<long long>> mat = base;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = mat[i][j] * diff[i][j] % MOD;
            }
        }
        return mat;
    }

    void printDiffMarks() const {
        cout << "Mult marks (" << rows + 1 << "x" << cols + 1 << "):\n";
        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j <= cols; j++) {
                cout << setw(4) << diff[i][j] % MOD << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    // ══════════════════════════════════════════════════════════════════════
    // DEMO 1 — DiffArray2DAdd
    // ══════════════════════════════════════════════════════════════════════
    cout << "=== DiffArray2DAdd (submatrix +val) ===\n\n";

    int rows = 4, cols = 4;
    vector<vector<long long>> base(rows, vector<long long>(cols, 0));

    DiffArray2DAdd daAdd(rows, cols);
    daAdd.rangeAdd(0, 0, 1, 1, 5);   // top-left 2x2 +5
    daAdd.rangeAdd(0, 0, 3, 3, 1);   // poori matrix +1
    daAdd.rangeAdd(1, 1, 2, 2, 10);  // center +10

    daAdd.printDiffMarks();
    auto addResult = daAdd.buildFinalMatrix(base);
    printMatrix(addResult, "\nAdd final matrix");

    cout << "\nSpot check (add):\n";
    cout << "(0,0) = " << addResult[0][0] << " (expect 6)\n";
    cout << "(1,1) = " << addResult[1][1] << " (expect 16)\n";
    cout << "(3,3) = " << addResult[3][3] << " (expect 1)\n";

    // ══════════════════════════════════════════════════════════════════════
    // DEMO 2 — DiffArray2DMultiply
    // ══════════════════════════════════════════════════════════════════════
    cout << "\n=== DiffArray2DMultiply (submatrix *val) ===\n\n";

    vector<vector<long long>> baseMult = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
    };

    DiffArray2DMultiply daMult(4, 4);
    daMult.rangeMultiply(0, 0, 1, 1, 2);   // top-left 2x2 *2
    daMult.rangeMultiply(2, 2, 3, 3, 3);   // bottom-right 2x2 *3

    daMult.printDiffMarks();
    auto multResult = daMult.buildFinalMatrix(baseMult);
    printMatrix(multResult, "\nMultiply final matrix");

    cout << "\nSpot check (mult mod " << MOD << "):\n";
    cout << "(0,0) = " << multResult[0][0] << " (expect 2)\n";
    cout << "(1,1) = " << multResult[1][1] << " (expect 2)\n";
    cout << "(2,2) = " << multResult[2][2] << " (expect 3)\n";
    cout << "(0,2) = " << multResult[0][2] << " (expect 1, untouched)\n";
    cout << "(3,3) = " << multResult[3][3] << " (expect 3)\n";

    // overlap test: center 2x2 *2, phir poori 3x3 top-left *3
    cout << "\n=== Multiply overlap test (3x3) ===\n";
    vector<vector<long long>> b2 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    DiffArray2DMultiply dm(3, 3);
    dm.rangeMultiply(1, 1, 2, 2, 2);   // center 4 cells *2
    dm.rangeMultiply(0, 0, 2, 2, 3);   // poori 3x3 *3
    auto m2 = dm.buildFinalMatrix(b2);
    printMatrix(m2, "Overlap result");
    // (1,1): 1*2*3=6, corners (0,0): 1*3=3

    cout << "(0,0) = " << m2[0][0] << " (expect 3)\n";
    cout << "(1,1) = " << m2[1][1] << " (expect 6)\n";

    return 0;
}
