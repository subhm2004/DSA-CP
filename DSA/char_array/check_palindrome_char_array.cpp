/*
 * ============================================================================
 * TOPIC    : Char Array
 * FILE     : check_palindrome_char_array.cpp
 * PROBLEM  : Check Palindrome Char Array
 * ABOUT    : C-style character arrays and string operations without STL string
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * checkpallindrome()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char ch[], int size
 * Returns : bool
 */
bool checkpallindrome(char ch[], int size){
    int i=0;
    int j= strlen(ch) -1;
    while(i<=j){
        if(ch[i]== ch[j]){
            i++;
            j--;
        }
        else{
            return false;
        }
    }
    return true;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Check Palindrome Char Array
 */
int main(){
    char ch[50];
    int size= 50;
    cout<< "enter character array"<< endl;
    cin.getline(ch,50);
    bool ans= checkpallindrome(ch,size);
    cout<< ans<< endl;


}
