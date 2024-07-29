# Check this out

```cpp
#include <algorithm>
#include <future>
#include <iostream>
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
  WaitingVehicles() : _tmpVehicles(0) {}

  // getters / setters
  void printSize() { std::cout << "#vehicles = " << _tmpVehicles << std::endl; }

  // typical behaviour methods
  void pushBack(Vehicle &&v) {
    //_vehicles.push_back(std::move(v)); // data race would cause an exception
    int oldNum = _tmpVehicles;
    std::this_thread::sleep_for(std::chrono::microseconds(
        1)); // wait deliberately to expose the data race
    _tmpVehicles = oldNum + 1;
  }

private:
  std::vector<Vehicle>
      _vehicles; // list of all vehicles waiting to enter this intersection
  int _tmpVehicles;
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
  std::chrono::microseconds(100);
  queue->printSize();

  return 0;
}
```

It seems that not all the vehicles could be added to the queue. But why is that?
Note that in the thread function `pushBack` there is a call to `sleep_for`,
which pauses the thread execution for a short time. This is the position where
the data race occurs: First, the current value of `_tmpVehicles` is stored in a
temporary variable `oldNum`. While the thread is paused, there might (and will)
be changes to `_tmpVehicles` performed by other threads. When the execution
resumes, the former value of `_tmpVehicles` is written back, thus invalidating
the contribution of all the threads who had write access in the mean time.

Interestingly, when sleep_for is commented out, the output of the program is
the same as with `std::launch::deferred` - at least that will be the case for
most of the time when we run the program. But once in a while, there might be
a scheduling constellation which causes the bug to expose itself. Apart from
understanding the data race, you should take as an advice that introducing
deliberate time delays in the testing / debugging phase of development can
help expose many concurrency bugs.
