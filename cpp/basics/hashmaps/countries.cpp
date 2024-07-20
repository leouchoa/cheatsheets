#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

int main() {

  std::unordered_map<int, std::string> mymap{
      {5, "a"}, {6, "b"}, {7, "c"}, {8, "d"}};

  for (const auto &pair : mymap) {
    std::cout << "Key: " << pair.first << ", Value: " << pair.second
              << std::endl;
  }
  // int maldives_key = 960;
  //   auto definitions = my_dictionary[key];
  // for (string definition : definitions) {
  //     cout << definition << "\n";
  // }
  // if (mymap[maldives_key]) {
};
}
;
