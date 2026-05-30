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


/*
 * main()
 * Purpose : Entry point — demo/test for Stl String Basics
 */
int main(){
    
    string str = "this is a car";
    str.erase(4,3);
    cout<< "after erasing: "<< str<< endl;
    string str2= "beautiful";
    str.insert(9,str2);
    cout<< "after inserting: "<< str << endl;
    string str1= "vanshika";
    str1.push_back('V');
    cout<< str1<< endl;
    str1.pop_back();
    cout<< str1<< endl;
    string str3 = "hello everyone myself vanshika";
    string str4 = "myself";
    if(str3.find(str4)== string::npos){
        cout<< "string not found"<< endl;
    }
    else {
        cout<< "string found"<< endl;
    }
    string str5= "vanshika";
    string str6= "vanshika";
    if(str5.compare(str6)== 0){
        cout<< "strings are equal"<< endl;
    }
    else{
        cout<< "strings are not equal"<< endl;
    }
    cout<< str3.substr(6,8)<< endl;




}
