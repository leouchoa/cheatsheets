# Should You Always Use Async?

Run the following code with the settings:

1. `int nLoops = 1e7 , nThreads = 4 , std::launch::async`
2. `int nLoops = 1e7 , nThreads = 5 , std::launch::deferred`
3. `int nLoops = 10 , nThreads = 5 , std::launch::async`
4. `int nLoops = 10 , nThreads = 5 , std::launch::deferred`

The conclusion would be that is therefore not a general advantage if
computations are performed in parallel: It must be carefully weighed with
regard to the computational effort whether parallelization makes sense.

```cpp
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

void workerFunction(int n) {
  // print system id of worker thread
  std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

  // perform work
  for (int i = 0; i < n; ++i) {
    sqrt(12345.6789);
  }
}

int main() {
  // print system id of worker thread
  std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

  // start time measurement
  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  // launch various tasks
  std::vector<std::future<void>> futures;

  int nLoops = 10, nThreads = 5;
  for (int i = 0; i < nThreads; ++i) {
    futures.emplace_back(std::async(workerFunction, nLoops));
  }

  // wait for tasks to complete
  for (const std::future<void> &ftr : futures)
    ftr.wait();

  // stop time measurement and print execution time
  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "Execution finished after " << duration << " microseconds"
            << std::endl;

  return 0;
}
```
