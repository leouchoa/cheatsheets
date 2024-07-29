# Deadlocks

Check this out:

```cpp
#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

double result;
// hey btw attention here:
// in the first time I was using `_mutex` because I copied from another
// private class attribute. It just didnt work....
std::timed_mutex mutex;

void printResult(int denom) {
  std::cout << "for denom = " << denom << ", the result is " << result
            << std::endl;
}

void divideByNumber(double num, double denom) {
  mutex.lock();
  try {
    // divide num by denom but throw an exception if division by zero is
    // attempted
    if (denom != 0) {
      result = num / denom;
      // exposing the data race
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
  mutex.unlock();
}

int main() {
  // create a number of threads which execute the function "divideByNumber" with
  // varying parameters
  std::vector<std::future<void>> futures;
  std::timed_mutex _mutex;
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

Here an exception was thrown while executing code in the critical section, i.e.,
between lock and unlock. In such a case, the mutex would remain locked
indefinitely and no other thread could unlock it - the program would most
likely freeze.
