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
class Animal{

    public:
    int age;
    int weight;
    string name;
    
    
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
};


/*
 * main()
 * Purpose : Entry point — demo/test for Oop Basics
 */
int main(){
    Animal a;
    a.age= 12;
    a.weight= 50;
    cout<< "age of a is:" << a.age<< endl;
    cout<< "weight of a is: "<< a.weight<< endl;
    a.eat();
    a.sleep();
    Animal* b= new Animal;
    b->age= 23;
    b->weight= 78;
    cout<< "age of b is: "<< b->age<< endl;
    cout<< "age of b is: "<< b->weight<< endl;
    b->eat();
    b->sleep();
    cout<< "size of class is: "<< sizeof(Animal)<< endl; 
}
