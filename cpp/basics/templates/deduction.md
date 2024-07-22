# Deduction

C++ can deduct/infer the type of the parameters so that you don't need
to specify it's type every time. But that only works fully on c++ 17.

```cpp
#include <assert.h>
#include <vector>

#include <assert.h>
#include <vector>

template <typename Type> Type Max(Type a, Type b) { return a > b ? a : b; }

int main() {
  std::vector v{1, 2, 3};
  assert(v.size() == 3);
}
int main() {
  // old
  // std::vector<int> v{1, 2, 3};
  // new, with deduction
  std::vector v{1, 2, 3};
  assert(v.size() == 3);
  // old
  // assert(Max<int>(10, 50) == 50);
  // assert(Max<double>(5.7, 1.436246) == 5.7);
  // new, with deduction
  assert(Max(10, 50) == 50);
  assert(Max(5.7, 1.436246) == 5.7);
}

```
