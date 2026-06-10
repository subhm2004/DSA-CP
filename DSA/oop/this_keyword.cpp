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

// ════════════════════════════════════════════════════════════════════════════
// THIS KEYWORD — parameter aur member name same hone pe resolve karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: this = current object ka pointer
// this->weight = parameter weight — shadowing avoid
// ════════════════════════════════════════════════════════════════════════════

class Animal{
    private:
    int weight; // private member
    public:
    
    // ── getweight: private weight return ─────────────────────────────────────
    //   1) weight member return karo
    int getweight(){
        return weight;
    }
    
    // ── setweight: this se member assign ─────────────────────────────────────
    //   1) this->weight = weight — param aur member alag
    //   2) this current object 'a' ko point karta hai
    void setweight(int weight){
       this-> weight = weight;  //this is a pointer to current object i.e. a
    }
};

// ── main: setweight aur getweight demo ───────────────────────────────────────
//   1) Animal a banao
//   2) setweight(78) — this keyword use
//   3) getweight se value print
int main() {
    Animal a;
    a.setweight(78);
    cout<< "weight of a is: "<< a.getweight() << endl;
}
