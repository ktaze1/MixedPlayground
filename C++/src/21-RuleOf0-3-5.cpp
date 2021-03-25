#include <cstring>
#include <iostream>
#include <string>

// Rule of Zero: any resource that needs to be managed should be in its own type

class cstring {
private:
  char *p;

public:
  ~cstring() { delete[] p; } // destructor
  cstring(cstring const &);  // constructor
  cstring(cstring &&);
  cstring &operator=(cstring const &);
  cstring &operator=(cstring &&);
};

class Person {
  cstring name;
  int arg;

public:
  ~Person() = default;
  Person(Person const &) = default;
  Person(Person &&) = default;
  Person &operator=(Person const &) = default;
  Person &operator=(Person &&) = default;
};

// Rule of Five: If a class requires ONE of five special member functions, and
// if move semantics are desired, then it most likely requires all five of them

class PersonR5 {
  char *name;
  int age;

public:
  ~PersonR5() { delete[] name; } // Destructor

  // Copy Semantics
  PersonR5(PersonR5 const &other) // Copy Constructor
      : name(new char[std::strlen(other.name) + 1]), age(other.age) {
    std::strcpy(name, other.name);
  }

  PersonR5 &operator=(PersonR5 const& other){ // Assignment
      PersonR5 copy(other);
      swap(*this, copy);
      return *this;
  }


  //Move Semantics
  PersonR5(PersonR5&& that) noexcept
    : name(nullptr), age(0){
        swap(*this, that);
    }

    PersonR5& operator=(PersonR5&& that) noexcept {
        swap(*this, that);
        return *this;
    }


    friend void swap(PersonR5& lhs, PersonR5& rhs) noexcept 
    {
        std::swap(lhs.name, rhs.name);
        std::swap(lhs.age, rhs.age);
    }
};