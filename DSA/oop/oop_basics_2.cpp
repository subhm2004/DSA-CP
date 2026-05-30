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
class A{
    public:
    int x;
    int *y = new int;
    int z;
    A(int x, int y, int z = 2){ //z is default argument
        this-> x = x;
        this-> y = new int(y) ;
        this-> z= z;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Oop Basics 2
 */
int main(){
    A obj(1,2);
    cout<< obj.x << " "<< obj.y << " "<< obj.z<<  endl;

}
