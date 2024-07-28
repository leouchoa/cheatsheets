# Running Multiple Threads

## Fork-Join Parallelism

Using threads follows a basic concept called "fork-join-parallelism". The
basic mechanism of this concept follows a simple three-step pattern:

1.Split the flow of execution into a parallel thread ("fork").
2.Perform some work in both the main thread and the parallel thread.
3.Wait for the parallel thread to finish and unite the split flow of execution
again ("join").

In the main thread, the program flow is forked into three parallel branches.
In both worker branches, some work is performed - which is why threads are
often referred to as "worker threads". Once the work is completed, the flow of
execution is united again in the main function using the `join()` command. In
this example, join acts as a barrier where all threads are united. The
execution of main is in fact halted, until both worker threads have
successfully completed their respective work.

```plaintext
     worker thread 1                  main thread                 worker thread 2
                                 ┌───────────────────┐
                                 │                   │
                                 │    start          │
                                 └───────────────────┘
                                         │
                                         ▼
                               ┌───────────────────┐
         ┌─────────────────────│       fork        │
         │                     └──────────┬────────┘
         │                     ┌───────────────────┐
         │                     │       fork        │─────────────────────┐
         │                     └──────────┬────────┘                     │
         │                                │                              │
         │                                │                              │
         ▼                                ▼                              ▼
  ┌──────│──────┐                 ┌─────────────┐                 ┌─────────────┐
  │  some work  │                 │  some work  │                 │  some work  │
  └──────┬──────┘                 └──────┬──────┘                 └──────┬──────┘
         │                               │                               │
         │                               ▼                               │
         │                         ┌─────────────┐                       │
         └────────────────────────>│    join     │<──────────────────────┘
                                   └──────┬──────┘
                                          │
                                          ▼
                                  ┌─────────────┐
                                  │   return    │
                                  └─────────────┘

```

## Example

```cpp
#include <iostream>
#include <thread>
#include <vector>

void printHello() {
  // perform work
  std::cout << "Hello from Worker thread #" << std::this_thread::get_id()
            << std::endl;
}

int main() {
  // create threads
  std::vector<std::thread> threads;
  for (size_t i = 0; i < 5; ++i) {
    // copying thread objects causes a compile error
    /*
    std::thread t(printHello);
    threads.push_back(t);
    */

    // moving thread objects will work
    threads.emplace_back(std::thread(printHello));
  }

  // do something in main()
  std::cout << "Hello from Main thread #" << std::this_thread::get_id()
            << std::endl;

  // call join on all thread objects using a range-based loop
  for (auto &t : threads)
    t.join();

  return 0;
}
```

Thread objects do not have a copy constructor and thus can not be duplicated.
If this were possible, we would create yet another branch in the flow of
execution, which is not what we want. The solution to this problem is to use
move semantics, which provide a convenient way for the contents of objects to
be 'moved' between objects, rather than copied. In this case we can use the
function `emplace_back()` instead of `push_back()`, which internally uses move
semantics to move our thread object into the vector without making a copy.

## Cool Bug: Attention With the Refs

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {

  std::vector<std::thread> threads;

  for (size_t i = 11; i > 0; --i) {

    threads.emplace_back(std::thread([i]() {
    // If you were to use the bellow, there would be a problem!
    // threads.emplace_back(std::thread([&i]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
      std::cout << "Hello from Worker thread #" << i << std::endl;
    }));
  }

  std::cout << "Hello from Main thread" << std::endl;

  for (auto &t : threads)
    t.join();

  return 0;
}

```
