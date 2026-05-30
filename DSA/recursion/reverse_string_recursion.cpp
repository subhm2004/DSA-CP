/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : reverse_string_recursion.cpp
 * PROBLEM  : Reverse String Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * printstr()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : string str
 * Returns : void
 */
void printstr(string str) {
    cout<< "string is: "<< " ";
    for(int i=0; i< str.length(); i++) {
        cout<< str[i];
    }
    cout<< endl;
}


/*
 * reversestring()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : string& str, int i, int j
 * Returns : void
 */
void reversestring(string& str, int i, int j) {
    printstr(str);
    if(i>j) {
        cout<< str << endl;
        return;
    }    
    swap(str[i], str[j]);
    reversestring(str, i+1, j-1);
}



/*
 * main()
 * Purpose : Entry point — demo/test for Reverse String Recursion
 */
int main() {
    string str = "vanshika";
    int i=0, j= str.length()-1;
    reversestring(str,i,j);
}
