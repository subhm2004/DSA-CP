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

// ════════════════════════════════════════════════════════════════════════════
// STRING BASICS — length, reverse, palindrome + STL string demo
// ────────────────────────────────────────────────────────────────────────────
// length(): manual char count — '\0' tak
// reverse(): two pointer swap
// pallindrome(): start/end compare
// main: STL string replace/erase demo
// COMPLEX: String ops O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── length: string ki length manually count karo ───────────────────────────
//   1) getline se input
//   2) i=0 se '\0' tak — har char pe count++
//   3) count return — strlen jaisa
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


// ── reverse: char array in-place reverse ─────────────────────────────────────
//   1) getline input
//   2) i=0, j=len-1 — swap until meet
//   3) in-place reverse complete
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


// ── printarray: char array print ─────────────────────────────────────────────
//   1) strlen tak characters print
void printarray(char arr[100]) {
    for(int i=0; i<strlen(arr); i++) {
        cout<< arr[i];
    }
}



// ── pallindrome: palindrome check ────────────────────────────────────────────
//   1) getline input
//   2) two pointer — ch[i]==ch[j] har step
//   3) mismatch pe false, poora match pe true
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



// ── main: STL string replace/erase demo ────────────────────────────────────
//   1) str me substring replace — str.replace(pos, len, newstr)
//   2) str.erase(pos, len) — characters hatao
int main() {
    char arr[100];
    string str;
  
   str = "this is my first message";
   string str2= "vanshika";
   str.replace(0,4,str2);  // pehle 4 chars ko str2 se replace
   cout<< str<< endl;
   str.erase(0,4);  // pehle 4 chars erase
   cout<< str<< endl;


}
