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



/*
 * find_length()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char str[]
 * Returns : int
 */
int find_length(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}



/*
 * reverse_string()
 * Purpose : Swap from both ends or reverse links iteratively.
 * Params  : char str[]
 * Returns : void
 */
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



/*
 * to_uppercase()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char str[]
 * Returns : void
 */
void to_uppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}



/*
 * replace_at_with_space()
 * Purpose : Standard DSA solution for this problem.
 * Params  : char str[]
 * Returns : void
 */
void replace_at_with_space(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@') {
            str[i] = ' ';
        }
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Char Array Basics
 */
int main() {
    char str[50];

    cout << "Enter a character array: ";
    cin.getline(str, 50);

    replace_at_with_space(str);
    cout << "After replacing @ with space: " << str << endl;

    return 0;
}
