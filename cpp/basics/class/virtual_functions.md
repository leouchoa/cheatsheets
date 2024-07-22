# Virtual Functions

They're like `ABC`s in python. Example:

```cpp
#include <cassert>
#include <iostream>

class Animal {
  virtual void Talk() const = 0;
  virtual std::string Race() const = 0;
};

class Human : public Animal {
public:
  void Talk() const { std::cout << "Humans talk\n"; }
  std::string Race() const { return "human"; }
};

int main() {
  Human human;
  human.Talk();
  assert(human.Race() == "human");
};
```

## Virtual Functions vs Pure Virtual Functions

In C++, both virtual functions and pure virtual functions are used in the context of polymorphism and inheritance, but they serve different purposes and have different implications for the design of a class hierarchy. Here are the key differences:

### Virtual Function

#### Definition

A virtual function is a function in a base class that can be overridden in a
derived class.

#### Implementation

A virtual function may have an implementation in the base class. Derived
classes can override this function to provide their own implementation.

#### Usage

When you call a virtual function on an object, the version of the function
that gets executed is determined at runtime based on the actual type of the
object (dynamic dispatch).

```cpp
class Base {
public:
  virtual void func() {
      // Base class implementation
  }
};

class Derived : public Base {
public:
  void func() override {
      // Derived class implementation
  }
};
```

#### Instantiation

You can create instances of a class with virtual functions, even if the
virtual function is not overridden in derived classes.

### Pure Virtual Function

#### Definition

A pure virtual function is a virtual function that must be overridden in any
derived class. It does not have an implementation in the base class.

#### Implementation

A pure virtual function is declared by assigning 0 in the declaration, and it
cannot have an implementation in the base class.

#### Usage

A class with at least one pure virtual function becomes an abstract class,
meaning you cannot instantiate objects of this class directly. It is intended
to be a base class for other classes.

```cpp
class Base {
public:
    virtual void func() = 0;  // Pure virtual function
};

class Derived : public Base {
public:
    void func() override {
        // Derived class implementation
    }
};
```

#### Instantiation

You cannot create instances of an abstract class (a class with at least one
pure virtual function). You must derive a class from it and implement all pure
virtual functions to create instances of the derived class.

#### Full Example

```cpp
# include <iostream>

// Base class with a virtual function and a pure virtual function
class Base {
public:
    // Virtual function with an implementation
    virtual void virtualFunc() {
        std::cout << "Base virtual function" << std::endl;
    }

    // Pure virtual function, no implementation
    virtual void pureVirtualFunc() = 0;
};

// Derived class overrides both virtual functions
class Derived : public Base {
public:
    void virtualFunc() override {
        std::cout << "Derived virtual function" << std::endl;
    }

    void pureVirtualFunc() override {
        std::cout << "Derived pure virtual function" << std::endl;
    }
};

int main() {
    Derived d;
    Base* b = &d;

    b->virtualFunc();       // Output: "Derived virtual function"
    b->pureVirtualFunc();   // Output: "Derived pure virtual function"

    return 0;
}
```
