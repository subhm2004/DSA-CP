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
class Maths{
    public:
    
    
    /*
     * sum()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int a, int b
     * Returns : int
     */
    int sum(int a, int b){
        cout << "I'M inside function 1"<< endl;
        return a+b;
    }
    
    
    /*
     * sum()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int a, int b, int c
     * Returns : int
     */
    int sum(int a, int b, int c){
        cout<< "I'm inside second function"<< endl;
        return a+b+c;
    }
    
    
    /*
     * sum()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int a, float b
     * Returns : float
     */
    float sum(int a, float b){
        cout<< "I'm inside third function"<< endl;
        return a+b;
    }
};
class Parameter{
    public:
    int value;
    int operator +(const Parameter &object2){
        int value1= this-> value;
        int value2= object2.value;
        return value1- value2;
    }
};

class Animal{
    public:
    
    
    /*
     * speak()
     * Purpose : Standard DSA solution for this problem.
     * Returns : virtual void
     */
    virtual void speak(){
        cout<< "speaking up"<< endl;
    }
};
class Dog: public Animal{
    public:
    
    
    /*
     * speak()
     * Purpose : Standard DSA solution for this problem.
     * Returns : virtual void
     */
    virtual void speak(){
        cout<< "Barking"<< endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Polymorphism
 */
int main(){
    Animal *a= new Animal();
    a->speak();
    Animal *b= new Dog();
    b-> speak();
    Dog *d= new Dog();
    d-> speak();
    Dog *e= (Dog*)new Animal();
    e-> speak();



}
