#include <assert.h>
#include <string>

// class Person {
// public:
//   Person(std::string s) : name(s) {}
//   std::string name;
// };

// in this case this is better because
// the class was not doing much to need private
// stuff. So using struct is better because
// everything is already public
struct Person {
  Person(std::string s) : name(s) {}
  std::string name;
};

// Test
int main() {
  Person alice("Alice");
  Person bob("Bob");
  assert(alice.name != bob.name);
}
