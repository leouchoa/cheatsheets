# Lambda Functions

Just take care with the `mutable` keyword, as the following example shows:

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
