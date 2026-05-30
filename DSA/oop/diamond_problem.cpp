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
class A{
    public:
    int chemistry;
    A() {
        chemistry= 45;
    }

};
class B{
    public:
    int chemistry;
    B() {
        chemistry= 67;
    }
};
class C: public A, public B{
    public:
    int maths;

};


/*
 * main()
 * Purpose : Entry point — demo/test for Diamond Problem
 */
int main(){
    C obj;
    cout<<  obj.B::chemistry<< " "<< obj.maths<< endl;
}
