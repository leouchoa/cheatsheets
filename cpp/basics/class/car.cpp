#include "car.h"
#include <iostream>

void Car::PrintCarData() {
  cout << "The distance that the " << color << " car " << number
       << " has traveled is: " << distance << "\n";
}

void Car::IncrementDistance() { distance++; }
