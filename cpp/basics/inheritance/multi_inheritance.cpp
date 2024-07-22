#include <cassert>

class Vehicle {};

class Car : public Vehicle {
public:
  int wheels{4};
};

class Sedan : public Car {
public:
  bool trunk{true};
  int seats{4};
};

int main() {
  Sedan sedan;
  assert(sedan.trunk == true);
  assert(sedan.seats == 4);
  assert(sedan.wheels == 4);
}
