# Reading Memory Info With `lldb`

`lldb` is the debug that comes with `llvm`, an alternative to `gdb` that works
on arm-based macos.

The c++ code bellow loads `str1` into memory.

```cpp
#include <stdio.h>

int main() {
  char str1[] = "UDACITY";
  printf("%s", str1);

  return 0;
}
```

To read it with `lldb`:

1. Compile the code with symbols using `clang`: `clang++ -g -std=c++17 main.cpp`
2. Run `lldb`: `lldb a.out`.
3. Set breakpoint after loading data into memory: `b 5`.
4. Run it: `run`.
5. It will stop at the breakpoint, then print the memory address: `p &str1`.
6. Finally: `memory read --format binary --size 1 0x00007ffee1f34b40 --count 7`.
