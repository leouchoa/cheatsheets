#include <cassert>
#include <iostream>

class Date {
public:
  Date(int day, int month, int year) {
    Day(day);
    Month(month);
    Year(year);
  };
  int Day() { return day; }
  void Day(int d) {
    if (d >= 1 && d <= 31)
      day = d;
  }
  int Month() { return month; }
  void Month(int m) {
    if (m >= 1 && m <= 12)
      month = m;
  }
  int Year() { return year; }
  void Year(int y) { year = y; }

  void Print() const {
    std::cout << day << '/' << month << '/' << year << std::endl;
  }

private:
  int day{1};
  int month{1};
  int year{0};
};

// Test in main
int main() {
  Date date(8, 5, 1981);
  assert(date.Day() == 8);
  assert(date.Month() == 5);
  assert(date.Year() == 1981);
  date.Print();
};
