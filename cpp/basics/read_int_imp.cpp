#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::istringstream;
using std::string;

int main() {
  string a("1 2 3");

  istringstream my_stream(a);

  int n;

  while (my_stream >> n) {
    cout << "That stream was successful: " << n << "\n";
  }
  cout << "The stream has failed." << "\n";
}
