/*
 * ============================================================================
 * TOPIC    : Strings
 * FILE     : string_practice_2.cpp
 * PROBLEM  : String Practice 2
 * ABOUT    : String manipulation with STL
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * removeduplicate()
 * Purpose : Hash set or sorting to find duplicates.
 * Params  : string& str
 * Returns : void
 */
void removeduplicate(string& str){
    string str1= "";
    int i=0;
    while(i!= str.length()){
        if(str1.length()>0){
            if(str[i]!= str1[str1.length()-1]){
                str1.push_back(str[i]);
            }
            else{
                str1.pop_back();
            }
        }
        else{
            str1.push_back(str[i]);
        }
        i++;    
    }
    cout<< str1<< endl;
}


/*
 * main()
 * Purpose : Entry point — demo/test for String Practice 2
 */
int main(){
    string str= "abbaca";
    removeduplicate(str);

}
