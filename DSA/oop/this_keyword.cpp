/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : this_keyword.cpp
 * PROBLEM  : This Keyword
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Animal{
    private:
    int weight;
    public:
    
    
    /*
     * getweight()
     * Purpose : Standard DSA solution for this problem.
     * Returns : int
     */
    int getweight(){
        return weight;
    }
    
    
    /*
     * setweight()
     * Purpose : Standard DSA solution for this problem.
     * Params  : int weight
     * Returns : void
     */
    void setweight(int weight){
       this-> weight = weight;  //this is a pointer to current object i.e. a
    }
};


/*
 * main()
 * Purpose : Entry point — demo/test for This Keyword
 */
int main() {
    Animal a;
    a.setweight(78);
    cout<< "weight of a is: "<< a.getweight() << endl;
}
