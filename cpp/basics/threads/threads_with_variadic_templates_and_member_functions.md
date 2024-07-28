# Threads With Variadic Templates and Member Functions

## Simple Example With Move Semantics

```cpp
#include <iostream>
#include <string>
#include <thread>

void printName(std::string name, int waitTime) {
  std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
  std::cout << "Name (from Thread) = " << name << std::endl;
}

int main() {
  std::string name1 = "MyThread1";
  std::string name2 = "MyThread2";

  // starting threads using value-copy and move semantics
  std::thread t1(printName, name1, 50);
  std::thread t2(printName, std::move(name2), 100);

  t1.join();
  t2.join();

  std::cout << "Name (from Main) = " << name1 << std::endl;
  std::cout << "Name (from Main) = " << name2 << std::endl;

  return 0;
}
```

## Use `std::ref` if Passing Refs to Threads

Otherwise you'll get a nasty error.

```cpp
#include <iostream>
#include <thread>

void printNumber(int &data) {
  data = 20;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Done with printNumber!" << data << std::endl;
};

int main() {
  int data = 10;

  std::thread t1(printNumber, std::ref(data));

  // printNumber(std::move(data));
  std::cout << data << std::endl;

  t1.join();
  std::cout << "Done! Data = " << data << std::endl;
};
```

## Using Member Functions

For calling member functions, the `std::thread` function requires an additional
argument for the object on which to invoke the member function.

```cpp
#include <iostream>
#include <thread>

class Vehicle {
public:
  Vehicle() : _id(0) {}
  void addID(int id) { _id = id; }
  void printID() {
      std::cout << "Vehicle ID=" << _id << std::endl;
  }

private:
  int _id;
};

int main() {
  Vehicle v1, v2;

  // call member function on object v
  std::thread t1 = std::thread(&Vehicle::addID, v1, 1);

  // call member function on object v
  std::thread t2 = std::thread(&Vehicle::addID, &v2, 2);

  //option 3: use shared pointers
  std::shared_ptr<Vehicle> v3(new Vehicle);
  std::thread t3 = std::thread(&Vehicle::addID, v, 1);

  // wait for thread to finish
  t1.join();
  t2.join();
  t3.join();

  // print Vehicle id
  v1.printID();
  v2.printID();
  v3->printID();

  return 0;
}
```

In the example above, the `Vehicle` object `v1` is passed to the thread function
by value, thus a copy is made which does not affect the "original" living in
the `main` thread. Changes to its member variable `_id` will thus not show when
printing calling `printID()` later in `main`. The second Vehicle object `v2` is
instead passed by reference. Therefore, changes to its `_id` variable will also
be visible in the main thread.

In regards to `v3`, it's an alternative to `v2`: we have to ensure that the
existence of `v2` outlives the completion of the thread `t2` - **otherwise
there will be an attempt to access an invalidated memory address**. An
alternative is to use a heap-allocated object and a reference-counted pointer
such as `std::shared_ptr<Vehicle>` to ensure that the object lives as long as
it takes the thread to finish its work. The following example shows how this
can be implemented:
