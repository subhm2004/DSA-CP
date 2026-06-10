/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : string_basics.cpp
 * PROBLEM  : String Basics
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STRING BASICS — STL string ke common operations demo
// ────────────────────────────────────────────────────────────────────────────
// Funda: length, empty, at/front/back, append se string properties samjho
// getline se poora line read hota hai (spaces ke saath)
// sizeof string object ka size hai, length() characters count karta hai
// ════════════════════════════════════════════════════════════════════════════

// ── main: string properties aur append demo ────────────────────────────────
//   1) getline se user se naam lo
//   2) length, empty, sizeof, at(2), front, back print karo
//   3) do strings banao — str1.append(str2) se join karo
//   4) before/after append output dikhao
int main(){
    string name;
    cout<< "enter name"<< endl;
    getline(cin,name); // poori line read — space bhi include
    cout<< "length is: "<< name.length()<< endl; // character count
    cout<< "is string empty: "<< name.empty()<< endl; // true agar khaali
    cout<< "size taken by string is: "<< sizeof(name)<< endl; // object size (not char count)
    cout<< "character at index 2: "<< name.at(2)<< endl; // bounds-checked access
    cout<< "front character is: "<< name.front()<< endl; // pehla char
    cout<< "back character is: "<< name.back()<< endl; // aakhri char
    string str1= "vanshika";
    string str2= "aggarwal";
    cout<< "before joining: string1: "<< str1<< " and str2: "<< str2<< endl;
    str1.append(str2); // str2 ko str1 ke end me chipka do
    cout<< "after joining: "<< str1<< endl;
}
