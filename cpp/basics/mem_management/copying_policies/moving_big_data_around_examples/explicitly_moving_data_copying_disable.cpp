#include <iostream>

using namespace std;

// This class for managing a template-based heap resource implements move
// semantics
template <class T> class MyClass {
  T *data = nullptr;

public:
  MyClass() {}

  // move constructor
  MyClass(MyClass &&other) {
    data = other.data;
    other.data = nullptr;
  }

  // move assignment operator
  MyClass &operator=(MyClass &&other) {
    if (this != &other) {
      if (data) {
        delete data;
      }
      data = other.data;
      other.data = nullptr;
    }

    return *this;
  }

  ~MyClass() {
    if (data) {
      delete data;
    }
  }

private:
  // copy constructor
  MyClass(const MyClass &);

  // copy assignment operator
  MyClass &operator=(const MyClass &);
};

int main() {
  MyClass<double> h1;

  // using the `move` constructor to move data;
  MyClass<double> h2 = std::move(h1);
  // To disable copying for class MyClass:
  // set visibility of MyClass(const MyClass &) and of MyClass &operator=(const
  // MyClass &) to private
}
