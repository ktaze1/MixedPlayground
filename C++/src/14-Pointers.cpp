#include <iostream>

void pointerOps() {
  int var = 20;
  int *ptr;
  ptr = &var;

  std::cout << var << '\n'; // 20

  std::cout << ptr << '\n'; // outputs the location of the memory

  std::cout << *ptr << '\n'; // 20

  // don't confuse dereference operator with pointer declaration. They're
  // different things
}

// Pointer to members

// pointers to static member functions

typedef int
Fn(int); // Fn is a type-of function that accepts an int and return and int

int MyFn(int i) { return 2 * i; }

class Class {
public:
  static int Static(int i) { return 3 * i; }
};

// pointers to member functions

typedef int Fn2(int);

class Class2 {
public:
  int A(int a) { return 2 * a; }

  int B(int b) { return 3 * b; }
};

// pointer to member variables

class Class3 {
public:
  int x, y, z;
  char m, n, o;
};

int x; // global variable

// pointer to static member variable

class Class4 {
public:
  static int i;
};

int Class4::i = 1;

int j = 2; //another global variable

int main(){
  Fn *fn;

  fn = &MyFn; // point to one function
  fn(3);      // calls myfn

  fn = &Class::Static; // point to another function
  fn(4);               // calls static

  //--------------

  Class2 c;
  Class2 *p = &c;

  Fn2 Class2::*fn2; // fn2 is a pointer to a type-of Fn2 within Class2

  fn2 = &Class2::A;
  (c.*fn2)(5);

  //-------------

  Class3 c3;
  Class3 *p3 = &c3; // pointer to class

  int *p_i; // pointer to int

  p_i = &x;    // now pointing to global x;
  p_i = &c3.x; // now pointing to c3's x;

  int Class3::*p_C_i; // pointer to an int within Class3

  p_C_i = &Class3::x; // point to x within any Class
  int i = c3.*p_C_i;  // use p_c_i to fetch x from c3's instance


  //-------------

  int k = 3; // local variable

  int *ptr;

  ptr = &k; // point to k
  *ptr = 2; // modify k

  ptr = &j; // point to j
  *ptr = 5; // modify j

  ptr = &Class4::i; //point to Class4::i
  *ptr = 4; //modify it.
}

// To Be Continued...