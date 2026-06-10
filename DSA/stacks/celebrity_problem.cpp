/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : celebrity_problem.cpp
 * PROBLEM  : Celebrity Problem
 * LEETCODE : 277 — Find the Celebrity
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : Eliminate non-celebrity in O(n) comparisons.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CELEBRITY PROBLEM — stack se non-celebrity eliminate karo
// ────────────────────────────────────────────────────────────────────────────
// arr[i][j]=1 → i knows j; celebrity = koi nahi jaanta, sab use jaante hain
// do log compare → jo celebrity nahi wo stack se bahar
// ════════════════════════════════════════════════════════════════════════════

// ── celebrityperson: stack elimination se celebrity dhundho ─────────────────
//   1) sab indices stack mein push
//   2) jab tak 1 nahi bache — do pop, knows-matrix se eliminate
//   3) bacha hua candidate verify — sab usse jaante hain, wo kisi ko nahi
//   4) valid nahi → -1, warna celebrity index
int celebrityperson(int arr[][3], int &n) {
    stack<int> st;
    for (int i = 0; i < n; i++) {
        st.push(i);                        // sab log stack mein — elimination start
    }
    while (st.size() != 1) {
        int a = st.top();
        st.pop();                          // pehla candidate pop
        int b = st.top();
        st.pop();                          // doosra candidate pop
        if (arr[a][b]) {
            st.push(b);                    // a knows b → a celebrity nahi
        }
        if (arr[b][a]) {
            st.push(a);                    // b knows a → b celebrity nahi
        }
    }
    int i = st.top();
    int j = 0;
    while (j < n) {
        if (arr[i][j] == 0 && (arr[j][i] == 1 && arr[i][i]) == 0) {
            j++;
        } else {
            return -1;
        }
    }
    return i;
}

int main() {
    int n = 3;
    int arr[3][3] = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0},
    };

    int ans = celebrityperson(arr, n);
    cout << ans << endl;
}
