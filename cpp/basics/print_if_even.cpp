#include <iostream>
using std::cout;

int main() {
  int i = 0;

  while (i < 11) {
    if (i % 2 == 0) {
      cout << i << "\n";
    }
    i++;
  }
}
