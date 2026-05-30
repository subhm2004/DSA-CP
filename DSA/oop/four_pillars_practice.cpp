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
class Animal {
    public:
    Animal(){
        cout<< "constructor called of animal class"<< endl;
    }
    
    
    /*
     * speak()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void speak(){
        cout<< "speaking up"<< endl;
    }
};
class Dog: public Animal{
    public:
    Dog (){
        cout<< "constructor of dog class"<< endl;
    }
    
    
    /*
     * speak()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void speak(){
        cout<< "barking"<< endl;
    }   
};


/*
 * main()
 * Purpose : Entry point — demo/test for Four Pillars Practice
 */
int main(){
    Animal *a= new Animal();
    Dog *b= new Dog();
    Dog *c= (Dog*)new Animal();
    Animal *d= new Dog();

}
