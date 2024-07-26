# `Rvalue` References and Move Semantics

The important message of the function argument of `myFunction` to the
programmer is : The object that binds to the `rvalue` reference `&&`val is yours,
it is not needed anymore within the scope of the caller (which is main). As
discussed in the previous section on `rvalue` references, this is interesting
from two perspectives:

- Passing values like this improves performance as no temporary copy needs to
be made anymore and
- ownership changes, since the object the reference binds to has been
abandoned by the caller and now binds to a handle which is available only to
the receiver. This could not have been achieved with `lvalue` references as any
change to the object that binds to the `lvalue` reference would also be visible
on the caller side.

```cpp
#include <iostream>

void myFunction(int &&val) {
  std::cout << "val = " << val << std::endl;
}

int main() {
  myFunction(42);

  return 0; 
}
```

By the way: *`rvalue` references are themselves `lvalues`*, because when
the inside the `myFunction` scope, `val` is an `lvalue`. A reference is always
defined in a certain context. Even though the object it refers to (the
number 42) may be disposable, in the context it has been created (the `main` function), it
is not disposable (the context of the reference). So within the scope of
`myFunction`, `val` is an `lvalue` as it gives access to the memory location where
the number 42 is stored.

## Using `std::move`

If you wanted to assign 42 to a variable

```cpp
#include <iostream>

void myFunction(int &&val) {
  std::cout << "val = " << val << std::endl;
}

int main() {
  int myValue = 42;
  myFunction(myValue);

  return 0; 
}
```

You would an error and a note telling you that

> candidate function not viable: expects an rvalue for 1st argument.

It expects an `rvalue`, but you provided a `lvalue`. To solve this, you
have to explicitly move the variable with `std::move`.

```cpp
#include <iostream>

void myFunction(int &&val) {
  std::cout << "val = " << val << std::endl;
}

int main() {
  int myValue = 42;
  myFunction(std::move(myValue));

  return 0; 
}
```
