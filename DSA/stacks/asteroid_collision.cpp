/*
 * ============================================================================
 * TOPIC    : Stacks
 * FILE     : asteroid_collision.cpp
 * PROBLEM  : Asteroid Collision
 * LEETCODE : 735 — Asteroid Collision
 * ABOUT    : Stack, monotonic stack, and bracket problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ASTEROID COLLISION — + right, - left; collision pe bada survive
// ────────────────────────────────────────────────────────────────────────────
// stack mein asteroids; negative aaye aur top positive → collision
// equal size → dono destroy; bada wala bachega
// ════════════════════════════════════════════════════════════════════════════

// ── asteroidarray: collision simulate karo ──────────────────────────────────
//   1) pehla asteroid push
//   2) har naya: negative + top positive → collision resolve
//   3) bada survive push, chhota pop
//   4) warna direct push
void asteroidarray(vector<int> &asteroids) {
    stack<int> st;
    st.push(asteroids[0]);
    int index = 1;
    while (index < asteroids.size()) {
        if (asteroids[index] < 0 && st.top() > 0) {
            int element = max(abs(asteroids[index]), abs(st.top()));
            st.pop();                      // collision — purana hatao
            st.push(element);              // survivor push
        } else {
            st.push(asteroids[index]);     // no collision — seedha push
        }
        index++;
    }
}

int main() {
    vector<int> asteroids = {1, -2, 10, -5};
}
