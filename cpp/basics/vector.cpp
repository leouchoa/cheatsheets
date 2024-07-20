#include <iostream>
#include <vector>
using std::cout;
using std::vector;

int main() {
  // Three ways of declaring and initializing vectors.
  vector<int> v_1{0, 1, 2};
  vector<int> v_2 = {3, 4, 5};
  vector<int> v_3;
  vector<vector<int>> v{{1, 2}, {3, 4}};

  v_3 = {6};
  cout << "Great! A 2D vector has been created." << "\n";
  cout << "Everything worked!" << "\n";
}
