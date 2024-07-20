# Initializer Lists

Initialize member variables to specific values, just before the class
constructor runs. This initialization ensures that class members are
automatically initialized when an instance of the class is created.

```cpp
Date::Date(int day, int month, int year) : year_(year) {
  Day(day);
  Month(month);
}
```

In general, prefer initialization to assignment. Initialization sets the
value as soon as the object exists, whereas assignment sets
the value only after the object comes into being. **This means that assignment
creates and opportunity to accidentally use a variable before its value is set**.

**In fact, initialization lists ensure that member variables are initialized
before the object is created. This is why class member variables can be
declared `const`, but only if the member variable is initialized through an
initialization list. Trying to initialize a `const` class member within the body
of the constructor will not work**.

Initializer lists exist for a number of reasons. First, the compiler can
optimize initialization faster from an initialization list than from within the
constructor.

A second reason is a bit of a technical paradox. If you have a `const` class
attribute, you can only initialize it using an initialization list. Otherwise,
you would violate the `const` keyword simply by initializing the member in the
constructor!

The third reason is that attributes defined as references must use
initialization lists.
