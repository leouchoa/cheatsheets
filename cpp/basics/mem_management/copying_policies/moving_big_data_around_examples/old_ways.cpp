#include <vector>

using namespace std;

// pass back by pointer (old C++)
const int array_size = 1e6; // determines size of the random number array

vector<int> *RandomNumbers1() {
  vector<int> *random_numbers =
      new vector<int>(array_size); // allocate memory on the heap...

  for (int i = 0; i < array_size; i++) {
    int b = rand();
    (*random_numbers).push_back(b); // ...and fill it with random numbers
  }

  return random_numbers; // return pointer to heap memory
}

// pass back by reference (old C++)
void RandomNumbers2(vector<int> &random_numbers) {
  random_numbers.resize(array_size); // expand vector to desired size
  for (int i = 0; i < array_size; i++) {
    random_numbers[i] = rand();
  }
}

int main() {
  // wrooooooooooong
  // std::vector random_numbers_1 = *RandomNumbers1();
  // free(*random_numbers_1);

  vector<int> *random_numbers_1 = RandomNumbers1(); // return-by-pointer
  free(random_numbers_1);

  // got it!!
  vector<int> *second_vector = new vector<int>;
  RandomNumbers2(*second_vector);
  free(second_vector);
}
