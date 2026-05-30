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
class Animal{
    public:
    int age;
    int weight;
    
    
    /*
     * eat()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void eat(){
        cout<< "eating"<< endl;
    }
    
    
    /*
     * sleep()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void sleep(){
        cout<< "sleeping"<< endl;
    }
    Animal(){
        this->age= 12;
        this->weight=56;
        cout<< "constructor called"<< endl;
    }
    Animal(int age, int weight){
        this->age= age;
        this->weight= weight;
        cout<< "parameterised constructor called"<< endl;
    }
    Animal(Animal& obj){
        this->age = obj.age;
        this->weight = obj.weight;
        cout<< "copy constructor called" << endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Constructor
 */
int main(){
    Animal b;
    Animal* a= new Animal(12,56);
    Animal c= b;
}
