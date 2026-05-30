/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : basics_practice_1.cpp
 * PROBLEM  : Basics Practice 1
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <string.h>
using namespace std;


/*
 * length()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char arr[100]
 * Returns : int
 */
int length(char arr[100]) {
    cout<< "enter the string"<< endl;
    cin.getline(arr,100);
    int i=0, count=0;
    while(arr[i]!='\0') {
         count++;
         i++;
    }
    return count;
}


/*
 * reverse()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : char arr[100]
 * Returns : void
 */
void reverse(char arr[100]) {
    cout<< "enter the string"<< endl;
    cin.getline(arr,100);
    int i=0, j = strlen(arr) -1;
    while(i<=j) {
        int temp= arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}


/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char arr[100]
 * Returns : void
 */
void printarray(char arr[100]) {
    for(int i=0; i<strlen(arr); i++) {
        cout<< arr[i];
    }
}



/*
 * pallindrome()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char arr[100]
 * Returns : bool
 */
bool pallindrome(char arr[100]) {
    cout<< "enter string"<< endl;
    cin.getline(arr,100);
    int i=0, j= strlen(arr) -1;
    bool same= false;
    while(i<=j) {
        if(arr[i] == arr[j]) {
            same = true;
        }
        else {
            same= false;
            break;
        }
        i++;
        j--;
    }
    return same;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Basics Practice 1
 */
int main() {
    char arr[100];
    string str;
  
   str = "this is my first message";
   string str2= "vanshika";
   str.replace(0,4,str2);
   cout<< str<< endl;
   str.erase(0,4);
   cout<< str<< endl;


}
