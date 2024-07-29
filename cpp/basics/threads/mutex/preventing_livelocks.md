# Preventing Livelocks

As a rule of thumb, avoid using several mutexes at once. For the remaining
cases though, using `std::lock` is a safe way to avoid a livelock situation. The
following code causes a livelock:

```cpp
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1, mutex2;

void ThreadA() {
  // Creates deadlock problem
  std::lock_guard<std::mutex> lock2(mutex2);
  std::cout << "Thread A" << std::endl;
  std::lock_guard<std::mutex> lock1(mutex1);
}

void ThreadB() {
  // Creates deadlock problem
  std::lock_guard<std::mutex> lock1(mutex1);
  std::cout << "Thread B" << std::endl;
  std::lock_guard<std::mutex> lock2(mutex2);
}

void ExecuteThreads() {
  std::thread t1(ThreadA);
  std::thread t2(ThreadB);

  t1.join();
  t2.join();

  std::cout << "Finished" << std::endl;
}

int main() {
  ExecuteThreads();

  return 0;
}
```

To circumvent this problem, we use the `std::lock` function to ensure that
the lock happens in specified order:

```cpp
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1, mutex2;

void ThreadA() {
  // Ensure that locks are always executed in the same order
  std::lock(mutex1, mutex2);
  std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
  std::cout << "Thread A" << std::endl;
  std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
}

void ThreadB() {
  std::lock(mutex1, mutex2);
  std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
  std::cout << "Thread B" << std::endl;
  std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
}

void ExecuteThreads() {
  std::thread t1(ThreadA);
  std::thread t2(ThreadB);

  t1.join();
  t2.join();

  std::cout << "Finished" << std::endl;
}

int main() {
  ExecuteThreads();

  return 0;
}
```
