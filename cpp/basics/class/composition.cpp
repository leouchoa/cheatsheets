#include <assert.h>
#include <cmath>
// Define PI through a macro
#define PI 3.14159;

struct LineSegment {
public:
  double length;
};

class Circle {
public:
  // constructor
  Circle(LineSegment &radius);
  // declaration
  double Area();

private:
  // points to LineSegment.length
  // allows us to pass by ref, not needing to make a copy
  // of LineSegment struct
  LineSegment &radius_;
};

// definitions
Circle::Circle(LineSegment &radius) : radius_(radius) {}

double Circle::Area() { return pow(Circle::radius_.length, 2) * PI; }

int main() {
  LineSegment radius{3};
  Circle circle(radius);
  assert(int(circle.Area()) == 28);
}
