/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : constructor.cpp
 * PROBLEM  : Constructor
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONSTRUCTORS — default, parameterized, copy constructor
// ────────────────────────────────────────────────────────────────────────────
// Funda: constructor object banate waqt auto call hota hai
// Default — koi arg nahi; Parameterized — values pass; Copy — existing se copy
// ════════════════════════════════════════════════════════════════════════════

class Animal{
    public:
    int age;
    int weight;
    
    // ── eat: eating behavior ─────────────────────────────────────────────────
    //   1) "eating" print
    void eat(){
        cout<< "eating"<< endl;
    }
    
    // ── sleep: sleeping behavior ─────────────────────────────────────────────
    //   1) "sleeping" print
    void sleep(){
        cout<< "sleeping"<< endl;
    }
    // ── Animal(): default constructor ──────────────────────────────────────────
    //   1) age=12, weight=56 set karo
    //   2) "constructor called" print
    Animal(){
        this->age= 12;
        this->weight=56;
        cout<< "constructor called"<< endl;
    }
    // ── Animal(age,weight): parameterized constructor ──────────────────────────
    //   1) passed age, weight assign
    //   2) "parameterised constructor called" print
    Animal(int age, int weight){
        this->age= age;
        this->weight= weight;
        cout<< "parameterised constructor called"<< endl;
    }
    // ── Animal(obj): copy constructor ──────────────────────────────────────────
    //   1) obj se age, weight copy
    //   2) "copy constructor called" print
    Animal(Animal& obj){
        this->age = obj.age;
        this->weight = obj.weight;
        cout<< "copy constructor called" << endl;
    }
};

// ── main: teen constructor types demo ────────────────────────────────────────
//   1) Animal b — default ctor (stack)
//   2) new Animal(12,56) — parameterized ctor (heap)
//   3) Animal c = b — copy ctor
int main(){
    Animal b; // default constructor
    Animal* a= new Animal(12,56); // parameterized
    Animal c= b; // copy constructor
}
