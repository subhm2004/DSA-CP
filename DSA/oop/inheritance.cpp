/*
 * ============================================================================
 * TOPIC    : Oop
 * FILE     : inheritance.cpp
 * PROBLEM  : Inheritance
 * ABOUT    : Object-Oriented Programming concepts in C++
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

class Animal
{
public:
    
    
    /*
     * sound()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void sound()
    {
        cout << "Animal makes sound" << endl;
    }
};

class Dog : public Animal
{
public:
    
    
    /*
     * bark()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void bark()
    {
        cout << "Dog barks" << endl;
    }
};

class Fruit
{
public:
    string name;
};

class Mango : public Fruit
{
public:
    int weight;
};

class Alphonso : public Mango
{
public:
    int sugarLevel;
};

class A
{
public:
    int physics = 85;
};

class B
{
public:
    int chemistry = 90;
};

class C : public A, public B
{
public:
    int maths = 95;
};

class Parent
{
public:
    
    
    /*
     * show()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void show()
    {
        cout << "This is parent class" << endl;
    }
};

class Child1 : public Parent
{
};

class Child2 : public Parent
{
};

class Student
{
public:
    string name = "Rahul";
};

class Marks
{
public:
    int score = 88;
};

class Result : public Student, public Marks
{
public:
    
    
    /*
     * display()
     * Purpose : Standard DSA solution for this problem.
     * Returns : void
     */
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Score: " << score << endl;
    }
};



/*
 * main()
 * Purpose : Entry point — demo/test for Inheritance
 */
int main()
{
    cout << "\n--- Single Inheritance ---\n";
    Dog d;
    d.sound();
    d.bark();

    cout << "\n--- Multilevel Inheritance ---\n";
    Alphonso a;
    a.name = "Alphonso Mango";
    a.weight = 300;
    a.sugarLevel = 90;

    cout << a.name << " " << a.weight << "g " << a.sugarLevel << "%\n";

    cout << "\n--- Multiple Inheritance ---\n";
    C obj;
    cout << obj.physics << " " << obj.chemistry << " " << obj.maths << endl;

    cout << "\n--- Hierarchical Inheritance ---\n";
    Child1 c1;
    Child2 c2;
    c1.show();
    c2.show();

    cout << "\n--- Hybrid Inheritance ---\n";
    Result r;
    r.display();

    return 0;
}
