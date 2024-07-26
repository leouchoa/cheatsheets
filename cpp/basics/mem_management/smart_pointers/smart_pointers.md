# Smart Pointers

With smart pointers, resource acquisition occurs at the same time that the
object is initialized (when instantiated with `make_shared` or `make_unique`), so
that all resources for the object are created and initialized in a single line
of code.

In modern C++, raw pointers managed with `new` and `delete` should only be used in
small blocks of code with limited scope, where performance is critical
and ownership rights of the memory resource are clear.

Important points:

- Smart pointers always need to be declared on the stack, otherwise
the scoping mechanism would not work.

- The smart pointer is now responsible for deleting the memory that the raw
pointer specifies, which happens as soon as the smart pointer goes out of scope

- A smart pointer is a class template that is declared on the stack and then
initialized by a raw pointer (returned by `new` ) to a heap-allocated object.

- The smart pointer destructor contains the call to `delete`, and because the
smart pointer is declared on the stack, its destructor is invoked when the
smart pointer goes out of scope, even if an exception is thrown.

The smart pointers are:

1. The unique pointer `std::unique_ptr` is a smart pointer which exclusively
owns a dynamically allocated resource on the heap:

- There must not be a second unique pointer to the same resource.
- Useful when working with a temporary heap resource that is no longer
      needed once it goes out of scope.
- syntax: `std::unique_ptr<Type> p(new Type);`
- The unique must be your default option, unless you know for certain that
sharing is required at a later stage.
- Also remember unique pointers key feature which makes it so well-suited as a
return type for many functions: the possibility to convert it to a shared pointer!

2. The shared pointer `std::shared_ptr` points to a heap resource but does not
explicitly own it. There may even be several shared pointers to the same
resource, each of which will increase an internal reference count. As soon as
this count reaches zero, the resource will automatically be deallocated.

3. The weak pointer `std::weak_ptr` behaves similar to the shared pointer but
does not increase the reference counter.

## Basic Example Using Unique Pointers

```cpp
#include <memory>

void RawPointer()
{
    int *raw = new int; // create a raw pointer on the heap
    *raw = 1; // assign a value
    delete raw; // delete the resource again
}

void UniquePointer()
{
    std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
    *unique = 2; // assign a value
    // delete is not neccessary
}
```
