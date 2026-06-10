/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : oop_practice.cpp
 * PROBLEM  : Oop Practice
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// OOP PRACTICE — Animal class: encapsulation, constructors, destructor
// ────────────────────────────────────────────────────────────────────────────
// Funda: private age + getter/setter, default/param/copy ctor, destructor
// Heap object (new), dereference, copy constructor demo
// ════════════════════════════════════════════════════════════════════════════

class Animal{
    int age; // private — direct access nahi
    public:
    int weight;
    string name;
    
    // ── eat: eating behavior print ───────────────────────────────────────────
    //   1) "eating" message cout
    void eat(){
        cout<< "eating" << endl;
    }
    
    // ── sleep: sleeping behavior print ───────────────────────────────────────
    //   1) "sleeping" message cout
    void sleep(){
        cout<< "sleeping"<< endl;
    }
    
    // ── getage: private age return karo ──────────────────────────────────────
    //   1) age member return — encapsulation via getter
    int getage(){
        return age;
    }
    
    // ── setage: private age set karo ─────────────────────────────────────────
    //   1) this->age = age — parameter ko member me assign
    void setage(int age){
        this->age = age;
    }
    // ── Animal(): default constructor ────────────────────────────────────────
    //   1) weight=0, setage(0) — default values
    //   2) "constructor called" print
    Animal(){
        this-> weight= 0;
        this-> setage(0);
        cout<< "constructor called"<< endl;
    }
    // ── Animal(w,name): parameterized constructor ────────────────────────────
    //   1) weight aur name assign
    //   2) "parameterised constructor called" print
    Animal(int weight, string name){
        this-> weight= weight;
        this-> name= name;
        cout<< "parameterised constructor called"<< endl;
    }
    // ── Animal(obj): copy constructor ────────────────────────────────────────
    //   1) obj se weight, name copy karo
    //   2) "copy constructor called" print
    Animal(const Animal &obj){
        this-> weight= obj.weight;
        this-> name= obj.name;
        cout<< "copy constructor called"<<endl;
    }
    // ── ~Animal(): destructor ─────────────────────────────────────────────────
    //   1) cleanup message print — object destroy hote waqt
    ~Animal(){
        cout<< "I'm inside destructor"<< endl;
    }
};

// ── main: heap object, dereference, copy ctor demo ───────────────────────────
//   1) new Animal(77,"babbar") — heap pe object
//   2) (*b) aur b-> se members access
//   3) Animal c = *b — copy constructor trigger
int main(){
    Animal *b= new Animal(77,"babbar"); 
    cout<< "age is: "<< (*b).getage() << endl;
    cout<< "weight is: "<< (*b).weight << endl;
    cout<< "name is: "<< b-> name<< endl;
     Animal c= *b; // copy constructor — naya object same data se
 



}
