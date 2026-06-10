/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : head_and_tail_recursion.cpp
 * PROBLEM  : Head And Tail Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HEAD vs TAIL RECURSION — Print order ka farq
// ────────────────────────────────────────────────────────────────────────────
// Head (counting): pehle print, phir call -> n n-1 ... 1
// Tail (counting2): pehle call, phir print -> 1 2 ... n
// Same logic, sirf print/call order alag — output ulta
// ════════════════════════════════════════════════════════════════════════════

// ── counting: HEAD recursion — pehle print, baad me call ────────────────────
//   1) n==0 -> return
//   2) cout n — abhi print (descending order)
//   3) counting(n-1) — chhota number
void counting(int n) {
    if(n==0) {
        return ;
    }
    cout<< n<< " ";  // head — pehle kaam karo
    counting(n-1);
}

// ── counting2: TAIL recursion — pehle call, baad me print ───────────────────
//   1) n==0 -> return
//   2) counting2(n-1) — pehle chhota solve
//   3) cout n — wapas aate waqt print (ascending order)
void counting2(int n) {
    if(n==0){
        return;
    }
    counting2(n-1);  // tail — pehle recursive call
    cout<< n<< " ";
}

// ── main: dono types ka output compare ──────────────────────────────────────
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    counting(n);   // n se 1
    cout<< endl;
    counting2(n);  // 1 se n
}
