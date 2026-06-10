/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : polymorphism.cpp
 * PROBLEM  : Polymorphism
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// POLYMORPHISM — compile-time (overloading) + runtime (virtual override)
// ────────────────────────────────────────────────────────────────────────────
// Funda: same name different signatures = overloading
// virtual speak() = runtime pe actual object type decide karega
// Operator overloading bhi compile-time polymorphism hai
// ════════════════════════════════════════════════════════════════════════════

class Maths{
    public:
    
    // ── sum(a,b): 2 integers add — overload 1 ───────────────────────────────
    //   1) "function 1" print, return a+b
    int sum(int a, int b){
        cout << "I'M inside function 1"<< endl;
        return a+b;
    }
    
    // ── sum(a,b,c): 3 integers add — overload 2 ──────────────────────────────
    //   1) "second function" print, return a+b+c
    int sum(int a, int b, int c){
        cout<< "I'm inside second function"<< endl;
        return a+b+c;
    }
    
    // ── sum(a,b): int+float add — overload 3 ───────────────────────────────
    //   1) "third function" print, return a+b (float)
    float sum(int a, float b){
        cout<< "I'm inside third function"<< endl;
        return a+b;
    }
};

// ── Parameter: operator+ overload demo ───────────────────────────────────────
class Parameter{
    public:
    int value;
    // ── operator+: custom addition (actually subtraction) ────────────────────
    //   1) this->value aur object2.value lo
    //   2) value1 - value2 return — operator overloading
    int operator +(const Parameter &object2){
        int value1= this-> value;
        int value2= object2.value;
        return value1- value2;
    }
};

class Animal{
    public:
    
    // ── speak: virtual base method — runtime polymorphism ke liye ────────────
    //   1) "speaking up" print — override ho sakta hai
    virtual void speak(){
        cout<< "speaking up"<< endl;
    }
};
class Dog: public Animal{
    public:
    
    // ── speak: override — Dog ka behavior ────────────────────────────────────
    //   1) "Barking" print — virtual dispatch se call hoga
    virtual void speak(){
        cout<< "Barking"<< endl;
    }
};

// ── main: overloading + virtual dispatch experiments ─────────────────────────
//   1) Animal* a=new Animal — base speak()
//   2) Animal* b=new Dog — virtual: Dog ka speak() (runtime)
//   3) Dog* d=new Dog — direct Dog speak()
//   4) Dog* e=(Dog*)new Animal — unsafe cast, base speak()
int main(){
    Animal *a= new Animal();
    a->speak();
    Animal *b= new Dog(); // upcasting — virtual dispatch
    b-> speak(); // runtime: Dog::speak() — "Barking"
    Dog *d= new Dog();
    d-> speak();
    Dog *e= (Dog*)new Animal(); // unsafe downcast
    e-> speak();



}
