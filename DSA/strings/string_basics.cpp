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


/*
 * main()
 * Purpose : Entry point — demo/test for String Basics
 */
int main(){
    string name;
    cout<< "enter name"<< endl;
    getline(cin,name);
    cout<< "length is: "<< name.length()<< endl;
    cout<< "is string empty: "<< name.empty()<< endl;
    cout<< "size taken by string is: "<< sizeof(name)<< endl;
    cout<< "character at index 2: "<< name.at(2)<< endl;
    cout<< "front character is: "<< name.front()<< endl;
    cout<< "back character is: "<< name.back()<< endl;
    string str1= "vanshika";
    string str2= "aggarwal";
    cout<< "before joining: string1: "<< str1<< " and str2: "<< str2<< endl;
    str1.append(str2);
    cout<< "after joining: "<< str1<< endl;
}
