#include <iostream>
using std::cout;

class Human {};
class Alien {};
class Dog {};

void hello() { cout << "Hello!\n"; };
void hello(Human human) { cout << "Hello, Human!\n"; };
void hello(Alien alien) { cout << "Hello, Alien!\n"; };
void hello(Dog dog) { cout << "Hello, Dog!\n"; };

int main() {
  Human human;
  Alien alien;
  Dog dog;
  hello(human);
  hello(alien);
  hello(dog);
};
