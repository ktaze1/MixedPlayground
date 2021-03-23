

#include <algorithm>
#include <vector>
void Lambdas() {

  // [](){} empty lambda which does nothing

  int a{0};

  // auto f = []() { return a * 9;};  ERROR: a cannot be accessed
  auto f = [a]() { return a * 9; };   // OK, captured by value
  auto f2 = [&a]() { return a * 9; }; // by reference

  auto b = f();
}

void example() {
  std::vector<int> vec{1, 2, 3, 4, 5};

  int threshold = 10;

  auto it = std::find_if(vec.begin(), vec.end(),
                         [threshold](int value) { return value < threshold; });
}