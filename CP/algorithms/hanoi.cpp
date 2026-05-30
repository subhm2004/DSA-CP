#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

void tower(int n, char s, char h, char d) {
  if (n == 0) {
    return;
  }
  tower(n - 1, s, d, h);
  cout << "Move disk " << n << " from " << s << " to " << d << endl;
  tower(n - 1, h, s, d);
}

int main() {
  int n;
  cout << "Enter the number of disks: ";
  cin >> n;
  cout << "Total moves: " << (1 << n) - 1 << endl; // 2^n - 1
  cout << "The moves are:\n";

  // Start time
  auto start = chrono::high_resolution_clock::now();
  tower(n, 'A', 'C', 'B');
  // End time
  auto end = chrono::high_resolution_clock::now();

  // Calculate execution time
  double duration = chrono::duration<double>(end - start).count();
  cout << "Execution time: " << duration << " seconds" << endl;

  return 0;
}