#include <iostream>
#include <vector>
using std::cout;
using std::vector;

// Define a function "AdditionFunction" here.
// Instead of just two ints, this function should accept a vector<int>
// as the argument, and it should return the sum of all the ints in the vector.

int AdditionFunction(vector<int> vec) {
  int res = 0;
  for (int i : vec) {
    res = res + i;
  }
  return res;
}

int main() {
  vector<int> v{1, 2, 3, 4};

  cout << AdditionFunction(v) << "\n";
}
