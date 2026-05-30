/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : dsa_practice_1.cpp
 * PROBLEM  : Dsa Practice 1
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <random>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Dsa Practice 1
 */
int main() {
    int p;
    cout<<"Enter the value : "<<endl;
    cin>>p;
  vector<vector<bool>> cells(p, vector<bool>(p, false));
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, p-1);
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      if (i == 0 || i == p-1 || j == 0 || j == p-1) {
        cells[i][j] = true;
      } else {
        int r = dis(gen);
        if (r == 0) {
          cells[i][j] = true;
        }
      }
    }
  }
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      if (cells[i][j]) {
        cout << "*";
      } else {
        cout << " ";
      }
    }
    cout << endl;
  }
  int x, y;
  cout << "Enter your move (x, y): ";
  cin >> x >> y;
  if (x < 0 || x >= p || y < 0 || y >= p) {
    cout << "Invalid move." << endl;
    return 1;
  }
  cells[x][y] = true;
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      if (cells[i][j]) {
        cout << "*";
      } 
      else {
        cout << " ";
      }
    }
    cout << endl;

}
}
