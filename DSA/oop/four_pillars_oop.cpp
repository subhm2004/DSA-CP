/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : four_pillars_oop.cpp
 * PROBLEM  : Four Pillars Oop
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FOUR PILLARS — Encapsulation, Inheritance, Polymorphism, Abstraction
// ────────────────────────────────────────────────────────────────────────────
// Funda: private methods = encapsulation; dog:Animal = inheritance
// operator+ overload = polymorphism; private eat/sleep = data hiding
// ════════════════════════════════════════════════════════════════════════════

class Animal{
    public:
        int age;
        int weight;
    private:
        
        // ── eat: private method — bahar se access nahi ───────────────────────
        //   1) "eating" print — encapsulation demo
        void eat(){
            cout<< "eating"<< endl;
        }
        
        // ── sleep: private method ──────────────────────────────────────────────
        //   1) "sleeping" print
        void sleep(){
            cout<< "sleeping"<< endl;
        }
};
class dog: public Animal{
    public:
    
    // ── print: inherited public age print ────────────────────────────────────
    //   1) this->age cout — parent ka public member accessible
    void print(){
        cout<< this->age << endl;
       }
    
};
class parameter{
    public:
    int value;

    // ── operator+: addition operator overload ──────────────────────────────────
    //   1) this->value aur obj2.value lo
    //   2) value1 - value1 print — custom behavior
    void operator+(parameter &obj2){
        int value1= this->value;
        int value2= obj2.value;
        cout<< value1- value1<< endl;
    }
};

// ── main: encapsulation, inheritance, operator overload demo ─────────────────
//   1) Animal a, dog d1 — inheritance
//   2) parameter obj1, obj2 — operator+ test
//   3) d1.print() — inherited age (unset — garbage/default)
int main(){
    Animal a;
    dog d1;
    parameter obj1, obj2;
    obj1.value = 7;
    obj2.value = 2;
    obj1+obj2; // operator overload call
    

    
    d1.print();
    
}
