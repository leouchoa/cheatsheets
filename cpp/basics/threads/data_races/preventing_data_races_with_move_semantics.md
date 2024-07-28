# Preventing Data Races With Move Semantics

It should work, right?

```cpp
#include <future>
#include <iostream>
#include <thread>

class Vehicle {
public:
  // default constructor
  Vehicle() : _id(0), _name(new std::string("Default Name")) {
    std::cout << "Vehicle #" << _id << " Default constructor called"
              << std::endl;
  }

  // initializing constructor
  Vehicle(int id, std::string name) : _id(id), _name(new std::string(name)) {
    std::cout << "Vehicle #" << _id << " Initializing constructor called"
              << std::endl;
  }

  // copy constructor
  Vehicle(Vehicle const &src) {
    // QUIZ: Student code STARTS here
    _id = src._id;
    if (src._name != nullptr) {
      _name = new std::string;
      *_name = *src._name;
    }
    // QUIZ: Student code ENDS here
    std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
  };

  // setter and getter
  void setID(int id) { _id = id; }
  int getID() { return _id; }
  void setName(std::string name) { *_name = name; }
  std::string getName() { return *_name; }

private:
  int _id;
  std::string *_name;
};

int main() {
  // create instances of class Vehicle
  Vehicle v0;                 // default constructor
  Vehicle v1(1, "Vehicle 1"); // initializing constructor

  // launch a thread that modifies the Vehicle name
  std::future<void> ftr = std::async(
      [](Vehicle v) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)); // simulate work
        v.setName("Vehicle 2");
      },
      v0);

  v0.setName("Vehicle 3");

  ftr.wait();
  std::cout << v0.getName() << std::endl;

  return 0;
}
```

Well unless it gives you segfault. Explanation:

- When you use `std::move(v0),` you're transferring ownership of resources (in
this case, a `std::unique_ptr`)from `v0` to another instance (in the lambda
function executed by `std::async`).

- After the move, `v0` is left in a valid but unspecified state, meaning that
the `std::unique_ptr` inside `v0` no longer owns a resource.

Segmentation Fault:

- After moving `v0`, you're attempting to access its _name member using `v0`.
`getName()`. Since `v0` no longer owns a valid resource, this access leads to
undefined behavior and causes a segmentation fault.

To correct ensure that you don't access `v0` after it has been moved. Here are a
few different approaches to solving this issue:

- Avoid Accessing v0 After Moving:
  - Simply avoid accessing `v0` after moving it to another thread, as `v0's` state
  is unspecified after the move.

- Use a Shared Pointer Instead:
  - If you need to access the same resource across multiple threads without
  transferring ownership, use `std::shared_ptr` instead of `std::unique_ptr`.

- Correct the Thread Usage:
  - Make sure that your thread operations don't access moved-from objects
  unless necessary.

Here's a by not accessing `v0`:

```cpp
#include <future>
#include <iostream>
#include <memory>
#include <thread>

class Vehicle {
public:
  // default constructor
  Vehicle() : _id(0), _name(std::make_shared<std::string>("Default Name")) {
    std::cout << "Vehicle #" << _id << " Default constructor called"
              << std::endl;
  }

  // initializing constructor
  Vehicle(int id, std::string name)
      : _id(id), _name(std::make_shared<std::string>(name)) {
    std::cout << "Vehicle #" << _id << " Initializing constructor called"
              << std::endl;
  }

  // move constructor with shared pointer
  Vehicle(Vehicle &&src) : _id(src._id), _name(std::move(src._name)) {
    // move id to this and reset id in source
    src.setID(0);
    std::cout << "Vehicle #" << _id << " move constructor called" << std::endl;
  };

  // setter and getter
  void setID(int id) { _id = id; }
  int getID() const { return _id; }
  void setName(std::string name) { *_name = name; }
  std::string getName() const { return *_name; }

private:
  int _id;
  std::shared_ptr<std::string> _name;
};

int main() {
  // create instances of class Vehicle
  Vehicle v0;                 // default constructor
  Vehicle v1(1, "Vehicle 1"); // initializing constructor

  // launch a thread that modifies the Vehicle name
  std::future<void> ftr =
      std::async([](Vehicle v) { v.setName("Vehicle 2"); }, std::move(v0));

  ftr.wait();
  // Ensure that v0 is not accessed after move, or use a shared resource
  std::cout << v1.getName() << std::endl; // Safe to access v1

  return 0;
}
```
