#include <assert.h>
#include <string>

struct Person {
public:
  Person(std::string const &n) : name(n) {}
  std::string const name;
};

int main() {
  Person alice("Alice");
  Person bob("Bob");
  assert(alice.name != bob.name);
}
