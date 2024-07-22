# Friend Classes

In C++, friend classes provide an alternative inheritance mechanism to derived
classes. The main difference between classical inheritance and friend
inheritance is that a friend class can access private members of the base class,
which isn't the case for classical inheritance. In classical inheritance, a
derived class can only access public and protected members of the base class.

```cpp
#include <assert.h>

class Rectangle;

class Square {
public:
  Square(int s) : side(s) {}

private:
  int side;
  // here
  friend class Rectangle;
};

class Rectangle {
public:
  Rectangle(const Square& a);
  int Area() const;

private:
  int width {0};
  int height {0};
};

Rectangle::Rectangle(const Square& a) : width(a.side), height(a.side) {}

int Rectangle::Area() const { return width * height; }

int main() {
  Square square(4);
  Rectangle rectangle(square);
  assert(rectangle.Area() == 16); 
};
```
