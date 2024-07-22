# Polymorphism

Polymorphism is means "assuming many forms". In the context of object-oriented
programming, polymorphism describes a paradigm in which a function may behave
differently depending on how it is called. In particular, the function will
perform differently based on its inputs.

Polymorphism can be achieved in two ways in `C++:` overloading and overriding.
In `C++,` you can write two (or more) versions of a function with the same name.
This is called "overloading". Overloading requires that we leave the function
name the same, but modify the function signature. For example, we might
define the same function name with multiple different configurations of input
arguments. This example of class `Date` overloads:

```cpp
#include <ctime>

class Date {
public:
  Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}
  // automatically sets the Date to the current year
  Date(int day, int month) : day_(day), month_(month) {
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    year_ = timePtr->tm_year;
  }

private:
  int day_;
  int month_;
  int year_;
};
```
