/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : oop_basics_2.cpp
 * PROBLEM  : Oop Basics 2
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONSTRUCTOR ADVANCED — default args, this, dynamic memory in class
// ────────────────────────────────────────────────────────────────────────────
// Funda: z=2 default argument — A(1,2) call pe z auto 2
// y pointer hai — heap pe naya int allocate
// ════════════════════════════════════════════════════════════════════════════

class A{
    public:
    int x;
    int *y = new int; // pointer member — heap memory
    int z;
    // ── A(x,y,z): parameterized ctor with default z=2 ────────────────────────
    //   1) this->x = x assign
    //   2) this->y = new int(y) — heap pe copy
    //   3) this->z = z (default 2 agar pass na ho)
    A(int x, int y, int z = 2){ //z is default argument
        this-> x = x;
        this-> y = new int(y) ;
        this-> z= z;
    }
};

// ── main: default argument ctor demo ─────────────────────────────────────────
//   1) A obj(1,2) — z automatically 2
//   2) x, y (pointer address), z print
int main(){
    A obj(1,2);
    cout<< obj.x << " "<< obj.y << " "<< obj.z<<  endl;

}
