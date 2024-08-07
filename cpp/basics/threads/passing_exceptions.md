# Passing exceptions

Classic `try-catch`.

The future-promise communication channel may also be used for passing
exceptions. To do this, the worker thread simply sets an exception rather than
a value in the promise. In the parent thread, the exception is then re-thrown
once `get()` is called on the future.

```cpp
#include <future>
#include <iostream>
#include <thread>

void divideByNumber(std::promise<double> &&prms, double num, double denom) {
  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
  try {
    if (denom == 0)
      throw std::runtime_error("Exception from thread: Division by zero!");
    else
      prms.set_value(num / denom);
  } catch (...) {
    prms.set_exception(std::current_exception());
  }
}

int main() {
  std::promise<double> prms;
  std::future<double> ftr = prms.get_future();

  double num = 42.0, denom = 0.0;
  std::thread t(divideByNumber, std::move(prms), num, denom);

  // retrieve result within try-catch-block
  try {
    double result = ftr.get();
    std::cout << "Result = " << result << std::endl;
  } catch (std::runtime_error e) {
    std::cout << e.what() << std::endl;
  }

  // thread barrier
  t.join();

  return 0;
}
```
