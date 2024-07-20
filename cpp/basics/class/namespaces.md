# Namespaces

They allow programmers to group logically related variables and functions
together. Namespaces also help to avoid conflicts between two variables that
have the same name in different parts of a program.

```cpp
namespace English {
void Hello() { std::cout << "Hello, World!\n"; }
}  // namespace English

namespace Spanish {
void Hello() { std::cout << "Hola, Mundo!\n"; }
}  // namespace Spanish

int main() {
  English::Hello();
  Spanish::Hello();
}
```

In this example, we have two different void Hello() functions. If we put both of
these functions in the same namespace, they would conflict and the program
would not compile. However, by declaring each of these functions in a separate
namespace, they are able to co-exist. Furthermore, we can specify which function
to call by prefixing Hello() with the appropriate namespace, followed by the
`::` operator.
