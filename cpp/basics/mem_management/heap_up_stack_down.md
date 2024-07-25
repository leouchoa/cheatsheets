# Directions

The heap grows upwards and stack grows downwards. Example:

```cpp
#include <iostream>
#include <vector>

void recursiveFunction(int level) {
  int localVariable = level; // Local variable allocated on the stack
  std::cout << "Level: " << level << ", Address of localVariable: " << &localVariable << std::endl;

  if (level > 0) {
      recursiveFunction(level - 1);
  }
}

int main() {
  int stackVariable = 10;
  std::cout << "Address of stackVariable: " << &stackVariable << std::endl;

  int* heapVariable = new int;
  std::cout << "Address of heapVariable: " << heapVariable << std::endl;

  recursiveFunction(5);

  delete heapVariable;
  return 0;
}

```

## Typical Memory Layouts

+---------------------------+
|                           |
|         OS Kernel         |
|      (Unreadable)         |
|                           |
+---------------------------+
|                           |
|         Stack             |
|      (grows down)         |
|                           |
+---------------------------+
|                           |
|       Memory Mapped       |
|          Files            |
|                           |
+---------------------------+
|                           |
|          Heap             |
|      (grows up)           |
|                           |
+---------------------------+
|                           |
|          BSS              |
|(Uninitialized Static Vars)|
|                           |
+---------------------------+
|                           |
|          Data             |
| (Initialized Static Vars) |
|                           |
+---------------------------+
|                           |
|          Code             |
|        (Text)             |
|                           |
+---------------------------+
