# Scope Resolution Operator

`::` is the scope resolution operator. We can use this operator to specify
which namespace or class to search in order to resolve an identifier.

Each class provides its own scope. We can use the scope resolution operator to
specify identifiers from a class.

**This becomes particularly useful if we want to separate class declaration from
class definition.**

```cpp
class Date {
 public:
  int Day() { return day; }
  void Day(int day);  // Declare member function Date::Day().
  int Month() { return month; }
  void Month(int month) {
    if (month >= 1 && month <= 12) Date::month = month;
  }
  int Year() { return year; }
  void Year(int year) { Date::year = year; }

 private:
  int day{1};
  int month{1};
  int year{0};
};

// Define member function Date::Day().
void Date::Day(int day) {
  if (day >= 1 && day <= 31) Date::day = day;
}
```
