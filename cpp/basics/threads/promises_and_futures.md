# Promises and Futures

The most important thing to remember about this paradigm: they're mean to be
a "use-once" type of communication, from worker back to main.

## The promise - future communication channel

To create the channel, you make a promise (sends to the channel) and a future (
receives from the channel).

```cpp
#include <future>
#include <iostream>
#include <thread>

void modifyMessage(std::promise<std::string> &&prms, std::string message) {
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  std::string modifiedMessage = message + " has been modified";
  prms.set_value(modifiedMessage);
}

int main() {
  std::string messageToThread = "My Message";

  // create promise and future
  std::promise<std::string> prms;
  std::future<std::string> ftr = prms.get_future();

  // start thread and pass promise as argument
  std::thread t(modifyMessage, std::move(prms), messageToThread);

  std::cout << "Original message from main(): " << messageToThread << std::endl;

  // retrieve modified message via future and print to console
  std::string messageFromThread = ftr.get();
  std::cout << "Modified message from thread(): " << messageFromThread
            << std::endl;

  // thread barrier
  t.join();

  return 0;
}
```

Promises can not be copied, because the promise-future concept is a two-point
communication channel for one-time use. Therefore, we must pass the promise to
the thread function using `std::move`. The thread function takes the promise
as an `rvalue` reference in accordance with move semantics. The thread will
then, during its execution, use the promise to pass back the modified message.

Back in the main thread, we start listening on the other end of the
communication channel by calling the function `get()` on the future. This method
**will block until data is available** - which happens as soon as `set_value` has
been called on the promise (from the thread). If the result is movable (which
is the case for `std::string`), it will be moved - otherwise it will be copied
instead. After the data has been received, the modified message is printed to
the console.

## Setting a Wait Time

We can use the `promise.wait_for()` function to wait for a specified time.
That will return a `status` object, which we can check for the results and
appropriately deal with it.

```cpp
#include <cmath>
#include <future>
#include <iostream>
#include <thread>

void computeSqrt(std::promise<double> &&prms, double input) {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  double output = sqrt(input);
  prms.set_value(output);
}

int main() {
  double inputData = 42.0;

  // create promise and future
  std::promise<double> prms;
  std::future<double> ftr = prms.get_future();

  // start thread and pass promise as argument
  std::cout << "Started Computing the Square Root!" << std::endl;
  std::thread t(computeSqrt, std::move(prms), inputData);

  auto status = ftr.wait_for(std::chrono::milliseconds(500));

  if (status == std::future_status::ready) {
    std::cout << "Square Root Result from thread(): " << ftr.get() << std::endl;
  }

  //  timeout has expired or function has not yet been started
  else if (status == std::future_status::timeout ||
           status == std::future_status::deferred) {
    std::cout << "Too long of a computation, ending." << std::endl;
  }

  // thread barrier
  t.join();

  return 0;
}
```
