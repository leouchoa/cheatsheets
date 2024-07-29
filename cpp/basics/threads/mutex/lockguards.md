# Lockguards

In practice direct calls to `lock()` should be avoided! Imagine that while
working under the lock, a thread would throw an exception and exit the
critical section without calling the unlock function on the mutex. In such a
situation, the program would most likely freeze as no other thread could
acquire the mutex any more.

We can avoid this problem by creating a `std::lock_guard` object, which keeps an
associated mutex locked during the entire object life time. The lock is
acquired on construction and released automatically on destruction. This makes
it impossible to forget unlocking a critical section. Also, `std::lock_guard`
guarantees exception safety because any critical section is automatically
unlocked when an exception is thrown:

```cpp
#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
double result;

void printResult(int denom) {
  std::cout << "for denom = " << denom << ", the result is " << result
            << std::endl;
}

void divideByNumber(double num, double denom) {
  try {
    if (denom != 0) {
      // Note that there is no direct call to lock or unlock the mutex anymore.
      // We now have a std::lock_guard object that takes the mutex as an 
      // argument and locks it at creation. When the method divideByNumber 
      // exits, the mutex is automatically unlocked by the std::lock_guard 
      // object as soon as it is destroyed - which happens, when the local 
      // variable gets out of scope.
      std::lock_guard<std::mutex> lck(mtx);

      result = num / denom;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      printResult(denom);
    } else {
      throw std::invalid_argument("Exception from thread: Division by zero!");
    }
  } catch (const std::invalid_argument &e) {
    // notify the user about the exception and return
    std::cout << e.what() << std::endl;
    return;
  }
}

int main() {
  // create a number of threads which execute the function "divideByNumber" with
  // varying parameters
  std::vector<std::future<void>> futures;
  for (double i = -5; i <= +5; ++i) {
    futures.emplace_back(
        std::async(std::launch::async, divideByNumber, 50.0, i));
  }

  // wait for the results
  std::for_each(futures.begin(), futures.end(),
                [](std::future<void> &ftr) { ftr.wait(); });

  return 0;
}
```
