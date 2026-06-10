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

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME CHECK — char array ulta padho to same?
// ────────────────────────────────────────────────────────────────────────────
// Two pointers: i start se, j end se
// Dono chars match karte jao — middle tak
// Koi mismatch -> false; i > j ho gaya -> true (palindrome)
// ════════════════════════════════════════════════════════════════════════════

// ── checkpallindrome: char array palindrome hai? ──────────────────────────
//   1) i = 0 (start), j = strlen(ch) - 1 (end)
//   2) i <= j tab tak: ch[i] == ch[j] check
//   3) match -> i++, j--; mismatch -> false return
//   4) loop complete -> true (palindrome)
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

// ── main: user se input, palindrome check print ───────────────────────────
//   1) char ch[50] buffer, size = 50
//   2) cin.getline se string input
//   3) checkpallindrome call — true/false
//   4) result print (1 = palindrome, 0 = nahi)
int main(){
    char ch[50];
    int size= 50;
    cout<< "enter character array"<< endl;
    cin.getline(ch,50);
    bool ans= checkpallindrome(ch,size);
    cout<< ans<< endl;


}
