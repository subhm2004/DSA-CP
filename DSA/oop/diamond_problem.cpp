/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : diamond_problem.cpp
 * PROBLEM  : Diamond Problem
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIAMOND PROBLEM — multiple inheritance me ambiguous members
// ────────────────────────────────────────────────────────────────────────────
// Funda: C inherits A aur B — dono me chemistry hai, kaunsa?
// Scope resolution B::chemistry se explicitly B wala choose karo
// Virtual inheritance se fix hota hai — yahan basic demo
// ════════════════════════════════════════════════════════════════════════════

class A{
    public:
    int chemistry;
    // ── A(): base A constructor ──────────────────────────────────────────────
    //   1) chemistry = 45 set karo
    A() {
        chemistry= 45;
    }

};
class B{
    public:
    int chemistry;
    // ── B(): base B constructor ──────────────────────────────────────────────
    //   1) chemistry = 67 set karo
    B() {
        chemistry= 67;
    }
};
class C: public A, public B{
    public:
    int maths;

};

// ── main: diamond problem — scope resolution se resolve ──────────────────────
//   1) C obj banao — A aur B dono ke ctor call
//   2) obj.B::chemistry — explicitly B ka member access
//   3) obj.maths print (uninitialized — default garbage)
int main(){
    C obj;
    cout<<  obj.B::chemistry<< " "<< obj.maths<< endl; // B:: — ambiguity fix
}
