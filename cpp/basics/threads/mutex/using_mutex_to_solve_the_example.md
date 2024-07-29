# Using mutex to protect data

In its simplest form, using a mutex consists of four straight-forward steps:

1. Include the `<mutex>` header
2. Create an `std::mutex`
3. Lock the mutex using `lock()` before read/write is called
4. Unlock the mutex after the read/write operation is finished using `unlock()`

In order to protect the access to `_vehicles` from being manipulated by several
threads at once, a mutex has been added to the class as a private data member.
In the `pushBack` function, the mutex is locked before a new element is added to
the vector and unlocked after the operation is complete.

Note that the mutex is also locked in the function `printSize` just before
printing the size of the vector. The reason for this lock is two-fold: First,
we want to prevent a data race that would occur when a read-access to the
vector and a simultaneous write access (even when under the lock) would occur.
And second, we want to exclusively reserve the standard output to the console
for printing the vector size without other threads printing to it at the same time.

When this code is executed, 1000 elements will be in the vector. By using a
mutex to our shared resource, a data race has been effectively avoided.

```cpp
#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Vehicle {
public:
  Vehicle(int id) : _id(id) {}

private:
  int _id;
};

class WaitingVehicles {
public:
  WaitingVehicles() {}

  // getters / setters
  void printSize() {
    _mutex.lock();
    std::cout << "#vehicles = " << _vehicles.size() << std::endl;
    _mutex.unlock();
  }

  // typical behaviour methods
  void pushBack(Vehicle &&v) {
    _mutex.lock();
    _vehicles.emplace_back(std::move(v)); // data race would cause an exception
    _mutex.unlock();
  }

private:
  std::vector<Vehicle>
      _vehicles; // list of all vehicles waiting to enter this intersection
  std::mutex _mutex;
};

int main() {
  std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 1000; ++i) {
    Vehicle v(i);
    futures.emplace_back(std::async(
        std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
  }

  std::for_each(futures.begin(), futures.end(),
                [](std::future<void> &ftr) { ftr.wait(); });

  queue->printSize();

  return 0;
}
```

## Mutex Options

- `mutex`: provides the core functions `lock()` and `unlock()` and the non-blocking
`try_lock()` method that returns if the mutex is not available.
- `recursive_mutex`: allows multiple acquisitions of the mutex from the same
thread.
- `timed_mutex`: similar to mutex, but it comes with two more methods
`try_lock_for()` and `try_lock_until()` that try to acquire the mutex for a period
of time or until a moment in time is reached.
- `recursive_timed_mutex`: is a combination of `timed_mutex` and
`recursive_mutex`.

Example using `timed_mutex`:

```cpp
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Vehicle {
public:
  Vehicle(int id) : _id(id) {}
  int getID() { return _id; }

private:
  int _id;
};

class WaitingVehicles {
public:
  WaitingVehicles() {}

  // getters / setters
  void printSize() {
    _mutex.lock();
    std::cout << "#vehicles = " << _vehicles.size() << std::endl;
    _mutex.unlock();
  }

  // typical behaviour methods
  void pushBack(Vehicle &&v) {
    for (size_t i = 0; i < 3; ++i) {
      if (_mutex.try_lock_for(std::chrono::milliseconds(100))) {
        _vehicles.emplace_back(std::move(v));
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        _mutex.unlock();
        break;
      } else {
        std::cout << "Error! Vehicle #" << v.getID()
                  << " could not be added to the vector" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  }

private:
  std::vector<Vehicle>
      _vehicles; // list of all vehicles waiting to enter this intersection
  std::timed_mutex _mutex;
};

int main() {
  std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 1000; ++i) {
    Vehicle v(i);
    futures.emplace_back(std::async(
        std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
  }

  std::for_each(futures.begin(), futures.end(),
                [](std::future<void> &ftr) { ftr.wait(); });

  queue->printSize();

  return 0;
}

```
