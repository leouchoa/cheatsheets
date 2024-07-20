#include <iostream>
#include <vector>
using std::cout;
using std::vector;

// TODO: Add PrintBoard function here.

void PrintLine(vector<int> vec) {
  for (int i : vec) {
    cout << i;
  };
  cout << "\n";
};

void PrintBoard(vector<vector<int>> vec) {
  for (vector i : vec) {
    PrintLine(i);
  };
};

int main() {
  vector<vector<int>> board{{0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0}};
  // TODO: Call PrintBoard function here.
  PrintBoard(board);
}
