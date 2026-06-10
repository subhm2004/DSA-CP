/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : four_pillars_practice.cpp
 * PROBLEM  : Four Pillars Practice
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FOUR PILLARS PRACTICE — inheritance + polymorphism (method overriding)
// ────────────────────────────────────────────────────────────────────────────
// Funda: Dog extends Animal, speak() override — runtime polymorphism setup
// Pointer types aur casting experiments — learning demo
// ════════════════════════════════════════════════════════════════════════════

class Animal {
    public:
    // ── Animal(): base constructor ───────────────────────────────────────────
    //   1) "constructor called of animal class" print
    Animal(){
        cout<< "constructor called of animal class"<< endl;
    }
    
    // ── speak: base class virtual-like behavior ──────────────────────────────
    //   1) generic "speaking up" print
    void speak(){
        cout<< "speaking up"<< endl;
    }
};
class Dog: public Animal{
    public:
    // ── Dog(): derived constructor ─────────────────────────────────────────
    //   1) Animal ctor pehle, phir "constructor of dog class"
    Dog (){
        cout<< "constructor of dog class"<< endl;
    }
    
    // ── speak: override — Dog ka apna behavior ───────────────────────────────
    //   1) "barking" print — parent speak() hide ho jata hai
    void speak(){
        cout<< "barking"<< endl;
    }   
};

// ── main: pointer types aur polymorphism experiments ─────────────────────────
//   1) Animal* a = new Animal() — base pointer, base object
//   2) Dog* b = new Dog() — derived pointer, derived object
//   3) Dog* c = (Dog*)new Animal() — unsafe downcast demo
//   4) Animal* d = new Dog() — upcasting — base ptr, derived obj
int main(){
    Animal *a= new Animal();
    Dog *b= new Dog();
    Dog *c= (Dog*)new Animal(); // unsafe cast — learning only
    Animal *d= new Dog(); // upcasting — polymorphism ke liye base pointer

}
