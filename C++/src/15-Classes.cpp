#include <iostream>
class AFinal final {};

// class B : class AFinal {}; since A is final, you can't inherit

// Friendship

class Animal {
private:
  double weight;
  double height;

public:
  friend void printWeight(Animal animal);
  friend class AnimalPrinter;

  friend std::ostream &operator<<(std::ostream &os, Animal animal);
};

void printWeight(Animal animal) { std::cout << animal.weight; }

// virtual inheritance

// struct A {};
// struct B : public virtual A {};

// when b has virtual base A, it means that A will reside in most derived class
// of inheritence tree, and thus that most derived class is also responsible for
// init that virtual base

struct A {
  int member;
  A(int param) { member = param; }
};

struct B : virtual A {
  B() : A(5) {}
};

struct C : B {
  C() : A(88) {}
};

// private inheritance

class Base {
public:
  int move();
  int turn();
};

class Child : private Base {
public:
  using Base::turn;
};

void privateInheritance() {

  Child c;
  // c.move(); error!
  c.turn();
}

// unnamed struct/classes

void unnamedClass() {
  struct {
    float x;
    float y;
  } point;

  point.x = 42.0;
}

// static class members

// they're considered it to be in the class' scope, but they've static storage

class StaticExample {
  static int num_instances;
  int i; // not static

public:
  static std::string static_str;
  static int static_func();

  StaticExample() {
    ++num_instances;
  } // non-static member functions can modify static member vars

  void set_str(const std::string &str);
};

int StaticExample::num_instances;
std::string StaticExample::static_str = "Hello";

class Example {
  static int num_instances;

public:
  static std::string static_str;
  // Declaration.
};
int Example::num_instances;
// Definition.
std::string Example::static_str = "Hello."; // Definition.