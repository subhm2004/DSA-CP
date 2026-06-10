/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : oop_basics.cpp
 * PROBLEM  : Oop Basics
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// OOP BASICS — class, object, stack vs heap, member access
// ────────────────────────────────────────────────────────────────────────────
// Funda: class = blueprint, object = instance
// Dot (.) stack object, arrow (->) heap pointer se access
// ════════════════════════════════════════════════════════════════════════════

class Animal{

    public:
    int age;
    int weight;
    string name;
    
    // ── eat: behavior method ─────────────────────────────────────────────────
    //   1) "eating" print karo
    void eat(){
        cout<< "eating"<< endl;
    }
    
    // ── sleep: behavior method ───────────────────────────────────────────────
    //   1) "sleeping" print karo
    void sleep(){
        cout<< "sleeping"<< endl;
    }
};

// ── main: stack object 'a' aur heap object 'b' demo ──────────────────────────
//   1) Animal a — stack pe, dot operator se access
//   2) eat/sleep call, age/weight print
//   3) Animal* b = new Animal — heap pe, arrow operator
//   4) sizeof(Animal) — class ka memory size
int main(){
    Animal a; // stack object
    a.age= 12;
    a.weight= 50;
    cout<< "age of a is:" << a.age<< endl;
    cout<< "weight of a is: "<< a.weight<< endl;
    a.eat();
    a.sleep();
    Animal* b= new Animal; // heap object
    b->age= 23;
    b->weight= 78;
    cout<< "age of b is: "<< b->age<< endl;
    cout<< "age of b is: "<< b->weight<< endl;
    b->eat();
    b->sleep();
    cout<< "size of class is: "<< sizeof(Animal)<< endl; 
}
