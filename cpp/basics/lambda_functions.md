# Lambda Functions

## Lambda

A Lambda is a function object (a "functor"), so it has a type and can be
stored and passed around. Its result object is called a "closure", which can
be called using the operator `()`.

A lambda formally consists of three parts: a capture list `[]` , a parameter
list `()` and a main part `{}`.

- The capture list `[]`: By default, variables outside of the enclosing `{}`
around the main part of the Lambda can not be accessed. By adding a variable
to the capture list however, it becomes available within the Lambda either as
a copy or as a reference. The captured variables become a part of the Lambda.

- The parameter list `()`: The way parameters are passed to a Lambda is
basically identical to calling a regular function. If the Lambda takes no
arguments, these parentheses can be omitted.

By the way a Lambda does not exist at runtime. The runtime effect of a Lambda
is the generation of an object (the closure). The difference between a Lambda
and the corresponding closure is similar to the distinction between a class
and an instance of the class. A class exists only in the source code while the
objects created from it exist at runtime.

## Example 1

```cpp
#include <iostream>

int main() {
  int id = 0;

  auto f = [](const int id) { std::cout << "ID = " << id << std::endl; };

  f(id);

  return 0;
}
```

## Example 2

By default, variables in the capture block can not be modified within the
Lambda. Using the keyword "mutable" allows to modify the parameters captured
by copy, and to call their non-`const` member functions within the body of the
Lambda. Just take care with the `mutable` keyword, as the following example
shows:

```cpp
#include <iostream>

int main() {
  // create lambdas
  int id = 0; // Define an integer variable

  // auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id'
  // cannot be accessed

  id++;
  auto f1 = [id]() {
    std::cout << "ID = " << id << std::endl;
  }; // OK, 'id' is captured by value

  id++;
  auto f2 = [&id]() {
    std::cout << "ID = " << id << std::endl;
  }; // OK, 'id' is captured by reference

  // auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error,
  // 'id' may not be modified

  auto f4 = [id]() mutable {
    std::cout << "ID = " << ++id << std::endl;
  }; // OK, 'id' may be modified

  auto f5 = [&id]() { std::cout << "ID = " << ++id << std::endl; };

  // execute lambdas
  f1(); // i = 1
  f2(); // i = 2
  f4(); // i = 3
  f5(); // i = 3 wtf?
  f5(); // i = 4
  f5(); // i = 5

  return 0;
}
```

## Explanation

The mutable keyword allows the internal copy to be modified, so it increments
the captured `id` from 2 to 3. However, this change does not affect the actual
`id` variable outside the `lambda`.

| Lambda  | Initial `id` | Captured Value | Printed Value | External `id` After Execution |
|---------|--------------|----------------|---------------|-------------------------------|
| `f1`    | 1            | 1              | 1             | 1                             |
| `f2`    | 2            | 2 (by ref)     | 2             | 2                             |
| `f4`    | 2            | 2 (mutable)    | 3             | 2                             |
| `f5`    | 2            | 2 (by ref)     | 3             | 3                             |
| `f5`    | 3            | 3 (by ref)     | 4             | 4                             |
| `f5`    | 4            | 4 (by ref)     | 5             | 5                             |

So **Consider using mutable carefully, as it introduces another layer of state
management inside the lambda.**
