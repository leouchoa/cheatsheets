# Multiple Inheritance

The Core Guidelines have some worthwhile recommendations about how and when to
use multiple inheritance:

- ["Use multiple inheritance to represent multiple distinct interfaces"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces)
- ["Use multiple inheritance to represent the union of implementation attributes"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c136-use-multiple-inheritance-to-represent-the-union-of-implementation-attributes)

## The Diamond Problem

The diamond problem happens when implementing a base class'
method in different subclasses and then inheritance those different
method at the same time:

```cpp
#include <iostream>

// Base class
class A {
public:
    void show() {
        std::cout << "Class A show() function" << std::endl;
    }
};

// Derived class B inherits from A
class B : public A {
};

// Derived class C inherits from A
class C : public A {
};

// Derived class D inherits from both B and C
class D : public B, public C {
};

int main() {
    D d;
    // This line will cause ambiguity as to which show() method to call
    // d.show(); // Uncommenting this line will cause a compilation error

    // To resolve ambiguity, we need to specify the path to the show() method
    d.B::show(); // Calls show() from B's A
    d.C::show(); // Calls show() from C's A
}
```
