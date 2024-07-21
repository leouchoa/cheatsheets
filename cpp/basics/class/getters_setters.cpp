#include <cstring>
#include <iostream>
#include <string>

class Car {
private:
  int horsepower_;
  int weight_;
  std::string brand_;

public:
  Car(int horsepower, int weight, std::string brand);

  int GetHorsePower() const { return horsepower_; }
  void SetHorsePower(int horsepower);

  int GetWeight() const { return weight_; }
  void SetWeight(int weight);

  std::string GetBrand() const { return brand_; }
  void SetBrand(std::string brand);
};

Car::Car(int horsepower, int weight, std::string brand) {
  SetHorsePower(horsepower);
  SetWeight(weight);
  SetBrand(brand);
}

void Car::SetHorsePower(int horsepower) { horsepower_ = horsepower; }
void Car::SetWeight(int weight) { weight_ = weight; }
void Car::SetBrand(std::string brand) { brand_ = brand; }

int main() {
  Car car(150, 1200, "my Brand");
  std::cout << car.GetBrand() << "\n";
  car.SetBrand("Peugeot");
  std::cout << car.GetBrand() << "\n";
}
