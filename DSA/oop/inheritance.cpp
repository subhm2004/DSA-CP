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

// ════════════════════════════════════════════════════════════════════════════
// INHERITANCE TYPES — single, multilevel, multiple, hierarchical, hybrid
// ────────────────────────────────────────────────────────────────────────────
// Funda: child class parent ki properties/methods inherit karti hai
// public inheritance — parent ke public members child me accessible
// ════════════════════════════════════════════════════════════════════════════

// ── Single Inheritance: Dog extends Animal ───────────────────────────────────
class Animal
{
public:
    // ── sound: base class behavior ───────────────────────────────────────────
    //   1) generic animal sound print
    void sound()
    {
        cout << "Animal makes sound" << endl;
    }
};

class Dog : public Animal
{
public:
    // ── bark: Dog-specific method ────────────────────────────────────────────
    //   1) dog bark message print — Animal ki sound() bhi available
    void bark()
    {
        cout << "Dog barks" << endl;
    }
};

// ── Multilevel: Fruit → Mango → Alphonso ─────────────────────────────────────
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

// ── Multiple Inheritance: C inherits A + B ─────────────────────────────────────
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

// ── Hierarchical: Child1, Child2 dono Parent se ──────────────────────────────
class Parent
{
public:
    // ── show: parent class message ───────────────────────────────────────────
    //   1) "This is parent class" print
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

// ── Hybrid: Result = Student + Marks ─────────────────────────────────────────
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
    // ── display: inherited name aur score print ──────────────────────────────
    //   1) Student::name aur Marks::score use karo
    //   2) dono fields print
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Score: " << score << endl;
    }
};

// ── main: saari inheritance types demo ───────────────────────────────────────
//   1) Single — Dog sound + bark
//   2) Multilevel — Alphonso fields set/print
//   3) Multiple — C ke teen subjects
//   4) Hierarchical — Child1/Child2 show()
//   5) Hybrid — Result display()
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
