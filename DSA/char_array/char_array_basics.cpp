/*
 * ============================================================================
 * TOPIC    : Char Array
 * FILE     : char_array_basics.cpp
 * PROBLEM  : Char Array Basics
 * ABOUT    : C-style character arrays and string operations without STL string
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <cstring>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CHAR ARRAY BASICS — C-style strings without STL string
// ────────────────────────────────────────────────────────────────────────────
// char[] null-terminated ('\0' se end)
// Manual length, reverse, uppercase, replace operations
// strlen, swap, character arithmetic use karo
// ════════════════════════════════════════════════════════════════════════════

// ── find_length: null terminator tak length count ─────────────────────────
//   1) len = 0 se start
//   2) str[len] != '\0' tab tak len++
//   3) '\0' mila -> loop stop
//   4) len return — character count (excluding '\0')
int find_length(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// ── reverse_string: char array ko in-place reverse ────────────────────────
//   1) left = 0, right = strlen(str) - 1
//   2) left < right: swap(str[left], str[right])
//   3) left++, right-- — ends se middle tak
//   4) reversed string print
void reverse_string(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        swap(str[left], str[right]);
        left++;
        right--;
    }
    cout << str << endl;
}

// ── to_uppercase: lowercase letters ko uppercase mein convert ─────────────
//   1) har char i pe loop till '\0'
//   2) 'a'..'z' range check
//   3) str[i] - 'a' + 'A' — ASCII shift se uppercase
//   4) in-place modify
void to_uppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

// ── replace_at_with_space: '@' ko space se replace ──────────────────────────
//   1) har char scan till '\0'
//   2) str[i] == '@' ho to str[i] = ' '
//   3) baaki chars unchanged
//   4) in-place replacement
void replace_at_with_space(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@') {
            str[i] = ' ';
        }
    }
}

// ── main: user input, @ replace demo ──────────────────────────────────────
//   1) char str[50] buffer
//   2) cin.getline se input lo
//   3) replace_at_with_space call
//   4) modified string print
int main() {
    char str[50];

    cout << "Enter a character array: ";
    cin.getline(str, 50);

    replace_at_with_space(str);
    cout << "After replacing @ with space: " << str << endl;

    return 0;
}
