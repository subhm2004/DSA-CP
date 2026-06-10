/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : string_elements_recursion.cpp
 * PROBLEM  : String Elements Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STRING LINEAR SEARCH — Character target dhundho
// ────────────────────────────────────────────────────────────────────────────
// Index i se start — str[i]==target -> index print
// Har step i+1 — poori string traverse
// Multiple occurrences ke liye har match print hoga
// ════════════════════════════════════════════════════════════════════════════

// ── findelement: string me character target search ────────────────────────────
//   1) i>=size -> base case, return
//   2) str[i]==target -> index print
//   3) findelement(str, size, i+1, target) — aage badho
void findelement(string str, int size, int i, char target) {
    if(i>= size) {
        return;
    }
    if(str[i] == target) {
        cout<< "target found at index "<< i<< endl;
    }
    findelement(str, size, i+1, target);
}

// ── main: character search demo ─────────────────────────────────────────────
int main() {
    string str = "vanshika";
    int size = str.length();
    int i=0;
    char target = 'a';
    findelement(str, size, i, target);
    return 0;
}
