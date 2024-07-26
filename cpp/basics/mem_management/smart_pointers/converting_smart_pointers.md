# Converting Weak Smart Pointers

In (1), a conversion from unique pointer to shared pointer is performed.
It's achieved by using `std::move`, which calls the move assignment operator
on `sharedPtr1` and steals the resource from `uniquePtr`, while at the same
time invalidating its resource handle on the heap-allocated integer.

In (2), we convert a weak to shared pointer. To **avoid invalid memory access**,
you gotta make sure that the object will not be deallocated before your work
on it has been finished. To do this, convert a weak pointer to a shared
pointer by calling the `lock()` function on the weak pointer.

In (3), a raw pointer is extracted from a shared pointer. However, this
operation does not decrease the reference count within `sharedPtr2`. This means
that calling delete on `rawPtr` in the last line before main returns **will
generate a runtime error** as a resource is trying to be deleted which is
managed by `sharedPtr2` and has already been removed.

**Attention**: Note that there are no options for converting away from a
shared pointer. Once you have created a shared pointer, you must stick to it (
or a copy of it) for the remainder of your program!!

```cpp
#include <iostream>
#include <memory>

int main() {
  // construct a unique pointer
  std::unique_ptr<int> uniquePtr(new int);

  // (1) shared pointer from unique pointer
  std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);

  // (2) shared pointer from weak pointer
  std::weak_ptr<int> weakPtr(sharedPtr1);
  std::shared_ptr<int> sharedPtr2 = weakPtr.lock();

  // (3) raw pointer from shared (or unique) pointer
  int *rawPtr = sharedPtr2.get();
  delete rawPtr;

  return 0;
}
```
