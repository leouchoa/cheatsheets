# Classes in C++

Classes allow C++ programmers to aggregate data in a meaningful way. They are
particularly useful when member variables are related by an **invariant**.

## Invariants

An **invariant** is a rule that limits the values of member variables.
For example, in a `Date` class:

- The `day` cannot be less than 1 or exceed the maximum number of days in a month (28, 29, 30, or 31).
- The `month` must be between 1 and 12.

### Example: `Date` Class

Here’s a simple definition of a `Date` class:

```cpp
class Date {
  int day{1};
  int month{1};
  int year{0};
};

## Access Control

In a class, members are private by default, which means you cannot access them 
directly from outside the class. This is different from a struct, where members 
are public by default.

## Accessors and Mutators

To manage access to the private members, we use accessors (getters) and mutators
(setters):

```cpp
class Date {
 public:
  int Day() { return day_; }
  void Day(int d) { day_ = d; }

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};
```

## Adding Invariants

Now, let's add some invariants to the mutator:

```cpp
class Date {
 public:
  int Day() { return day_; }
  void Day(int d) {
    if (d >= 1 && d <= 31) day_ = d; // Invariant for day
  }

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};

```

## Summary

- Use classes when you need to enforce invariants on member variables.
- Keep member variables private to control access and enforce rules through
accessors and mutators.
