#include <cassert>

class Date {
public:
  // Date(int day, int month, int year);
  int Day() const { return day; }
  void Day(int day);
  int Month() const { return month; }
  void Month(int month);
  int Year() const { return year; }
  void Year(int year);

private:
  int day{1};
  int month{1};
  int year{0};
};

// Date::Date(int day, int month, int year) {
//   Day(day);
//   Month(month);
//   Year(year);
// }

void Date::Day(int day) {
  if (day >= 1 && day <= 31)
    Date::day = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    Date::month = month;
}

void Date::Year(int year) {
  if (year >= 12)
    Date::year = year;
}

// Test in main
int main() {
  Date date;
  date.Day(29);
  date.Month(8);
  date.Year(1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
}
