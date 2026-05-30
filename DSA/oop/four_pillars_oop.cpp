/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : four_pillars_oop.cpp
 * PROBLEM  : Four Pillars Oop
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
    private:
        
        
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
class dog: public Animal{
    public:
    
    
    /*
     * print()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void print(){
        cout<< this->age << endl;
       }
    
};
class parameter{
    public:
    int value;

    void operator+(parameter &obj2){
        int value1= this->value;
        int value2= obj2.value;
        cout<< value1- value1<< endl;
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for Four Pillars Oop
 */
int main(){
    Animal a;
    dog d1;
    parameter obj1, obj2;
    obj1.value = 7;
    obj2.value = 2;
    obj1+obj2;
    

    
    d1.print();
    
}
