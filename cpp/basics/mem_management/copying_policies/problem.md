# The Problem

The usual memory management practice is to wrap the things/pointers being
allocated (also called handles) inside a class because, well, it's c++.
However if you make copies of your class, which you are going to obviously,
c++ will make a shallow copy of the malloc pointers, **without allocating
new variables on the heap**. So, as the example shows, if you try to free,
both classes you'll end up trying to free the same thing twice. Damn.

```cpp
#include <iostream>

class MyClass {
private:
  int *_myInt;

public:
  MyClass() { _myInt = (int *)malloc(sizeof(int)); };
  ~MyClass() { free(_myInt); };
  void printOwnAddress() {
    std::cout << "Own address on the stack is " << this << std::endl;
  }
  void printMemberAddress() {
    std::cout << "Managing memory block on the heap at " << _myInt << std::endl;
  }
};

int main() {
  // instantiate object 1
  MyClass myClass1;
  myClass1.printOwnAddress();
  myClass1.printMemberAddress();

  // copy object 1 into object 2
  MyClass myClass2(myClass1); // copy constructor
  myClass2.printOwnAddress();
  myClass2.printMemberAddress();

  return 0;
}

```
