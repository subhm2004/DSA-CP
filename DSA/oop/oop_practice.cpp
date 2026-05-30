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

class Animal{
    int age;
    public:
    int weight;
    string name;
    
    
    /*
     * eat()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void eat(){
        cout<< "eating" << endl;
    }
    
    
    /*
     * sleep()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void sleep(){
        cout<< "sleeping"<< endl;
    }
    
    
    /*
     * getage()
     * Purpose : Standard DSA solution for this problem.
     * Returns : int
     */
    int getage(){
        return age;
    }
    
    
    /*
     * setage()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int age
     * Returns : void
     */
    void setage(int age){
        this->age = age;
    }
    Animal(){
        this-> weight= 0;
        this-> setage(0);
        cout<< "constructor called"<< endl;
    }
    Animal(int weight, string name){
        this-> weight= weight;
        this-> name= name;
        cout<< "parameterised constructor called"<< endl;
    }
    Animal(const Animal &obj){
        this-> weight= obj.weight;
        this-> name= obj.name;
        cout<< "copy constructor called"<<endl;
    }
    ~Animal(){
        cout<< "I'm inside destructor"<< endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Oop Practice
 */
int main(){
    Animal *b= new Animal(77,"babbar"); 
    cout<< "age is: "<< (*b).getage() << endl;
    cout<< "weight is: "<< (*b).weight << endl;
    cout<< "name is: "<< b-> name<< endl;
     Animal c= *b;
 



}
