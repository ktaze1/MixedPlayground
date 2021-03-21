#include <assert.h>
#include <iostream>
#include <vector>
void References() {
  int i = 10;
  int &referencei = i;

  referencei = 20; // i also is 20;

  // int &i; gives error at compile time. It must be initialized

  int *const ptr = nullptr; // allowed
                            // int &refi = nullptr;
}

// Semantics

/*
    A type has value semantics if the obj's observable state is functionally
   distinct from all other objects of that type. This means if you copy an obj,
   you have new obj.
*/

void valueSemantics() {
  int i = 5;
  int j = i;
  j += 20;
  std::cout << i; // prints 5

  std::vector<int> v1(5, 12); // vector of 5 elements, 12 in each
  std::vector<int> v2 = v1;   // copies v1;
}

/*
    Type has reference semantics if an instance of that tyoe can share the its
    observable state with another object, such that manipulating one cause other
   to change
*/

void referenceSemantics() {
  int *pi = new int(4);
  int *pi2 = pi;

  pi = new int(16);
  assert(pi2 != pi); // will alway pass

  int *pj = pi;
  *pj += 5;
  // pi is now 9
  delete pj;
}

// Deep copying and move support
namespace DeepCopy1 {

struct Inner {
  int i;
};

const int NUM_INNER = 5;
class Value {
private:
  Inner *array_; // Normally has reference semantics
public:
  Value() : array_(new Inner[NUM_INNER]) {} // default constructor

  ~Value() { delete[] array_; } // destructor

  Value(const Value &val) : array_(new Inner[NUM_INNER]) {
    for (int i{0}; i < NUM_INNER; ++i)
      array_[i] = val.array_[i];
  }

  Value &operator=(const Value &val) {
    for (int i{0}; i < NUM_INNER; ++i)
      array_[i] = val.array_[i];
    return *this;
  } // Deep copy
};

} // namespace DeepCopy1

namespace DeepCopy2 {
struct Inner {
  int i;
};

constexpr auto NUM_INNER = 5;

class Value {
private:
  Inner *array_; // Normally has reference semantics

public:
  Value() : array_(new Inner[NUM_INNER]) {}

  ~Value() { delete[] array_; } // ok to delete even if nullptr

  Value(const Value &val) : array_(new Inner[NUM_INNER]) {
    for (int i{0}; i < NUM_INNER; ++i)
      array_[i] = val.array_[i];
  }

  Value &operator=(const Value &val) {
    for (int i{0}; i < NUM_INNER; ++i)
      array_[i] = val.array_[i];
    return *this;
  }

  // Movement means no memory allocation
  // Cannot throw exceptions
  Value(Value &&val) noexcept : array_(val.array_) { val.array_ = nullptr; }

  Value &operator=(Value &&val) noexcept { std::swap(array_, val.array_); }
};
} // namespace DeepCopy2

// we can even make such a type non-copyable, if we want to forbid deep copies
// while still allowing the object to be moved around.

namespace DeepCopy3 {
struct Inner {
  int i;
};

constexpr auto NUM_INNER = 5;

class Value {

private:
  Inner *array_; // Normally has reference semantics.

public:
  Value() : array_(new Inner[NUM_INNER]) {}

  ~Value() { delete[] array_; } // OK to delete even if nullptr

  Value(const Value &val) = delete;

  Value &operator=(const Value &val) = delete;
  // Movement means no memory allocation.
  // Cannot throw exceptions.
  Value(Value &&val) noexcept : array_(val.array_) {
    // We've stolen the old value.
    val.array_ = nullptr;
  }
  // Cannot throw exceptions.
  Value &operator=(Value &&val) noexcept {
    // Clever trick. Since `val` is going to be destroyed soon anyway,
    // we swap his data with ours. His destructor will destroy our data.
    std::swap(array_, val.array_);
  }
};
} // namespace DeepCopy3
