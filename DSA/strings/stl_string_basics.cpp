/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : stl_string_basics.cpp
 * PROBLEM  : Stl String Basics
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// STL STRING OPERATIONS — erase, insert, push/pop, find, compare, substr
// ────────────────────────────────────────────────────────────────────────────
// Funda: STL string ke core methods ek program me practice karo
// erase(pos,len), insert(pos,str), find, compare, substr
// ════════════════════════════════════════════════════════════════════════════

// ── main: STL string methods ka hands-on demo ──────────────────────────────
//   1) erase — index 4 se 3 chars hatao
//   2) insert — position 9 pe "beautiful" daalo
//   3) push_back/pop_back — last char add/remove
//   4) find — substring search, npos = not found
//   5) compare — equal strings check (0 = equal)
//   6) substr — slice nikal ke print
int main(){
    
    string str = "this is a car";
    str.erase(4,3); // "is a" part erase — "this a car"
    cout<< "after erasing: "<< str<< endl;
    string str2= "beautiful";
    str.insert(9,str2); // position 9 pe insert
    cout<< "after inserting: "<< str << endl;
    string str1= "vanshika";
    str1.push_back('V'); // end me char add
    cout<< str1<< endl;
    str1.pop_back(); // last char hatao
    cout<< str1<< endl;
    string str3 = "hello everyone myself vanshika";
    string str4 = "myself";
    if(str3.find(str4)== string::npos){ // substring nahi mila
        cout<< "string not found"<< endl;
    }
    else {
        cout<< "string found"<< endl;
    }
    string str5= "vanshika";
    string str6= "vanshika";
    if(str5.compare(str6)== 0){ // lexicographic compare — 0 means equal
        cout<< "strings are equal"<< endl;
    }
    else{
        cout<< "strings are not equal"<< endl;
    }
    cout<< str3.substr(6,8)<< endl; // index 6 se 8 chars — "everyone"




}
