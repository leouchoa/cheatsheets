#include <assert.h>
#include <iostream>

class Point {
public:
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}

  //  Use of Const:
  //
  //  - Using const Point& as the parameter type avoids copying the parameter
  //  and ensures the parameter is not modified.
  //
  //  - Marking the function const ensures
  //  it doesn't modify the object it is called on.
  Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  std::cout << p1.x;
  Point p3 = p1 + p2; // An example call to "operator +";
  assert(p3.x == p1.x + p2.x);
  assert(p3.y == p1.y + p2.y);
}
