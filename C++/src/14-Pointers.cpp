#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

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

int j = 2; // another global variable

int main1() {
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

  ptr = &Class4::i; // point to Class4::i
  *ptr = 4;         // modify it.
}

// unique pointers

// dynamic obj is owned by only one instance at any time

void unqPtr() {
  std::unique_ptr<int> ptr = std::make_unique<int>(20);
  // create dynamic int with value of 20 owned by unique ptr

  std::unique_ptr<int[]> ptrArray = std::make_unique<int[]>(15);

  // use std::move( newSmartPointer ) to transfer ownership

  std::unique_ptr<int> newOwner = std::move(ptr);
  // ptr becomes nullptr

} // out of scope, unique ptr calls the destructor

// shared pointers

class Foo {};

void sharedPointers() {

  std::shared_ptr<Foo> firstShared = std::make_shared<Foo>();
  std::shared_ptr<Foo> secondShared(firstShared); // copy constructor
  secondShared = firstShared;                     // assignment

  std::shared_ptr<int[]> oldSh(
      new int[10],
      std::default_delete<int[]>()); // before c++17 you gotta specify deleter

  std::shared_ptr<int[]> sh(new int[10]); // this is c++17
  sh[0] = 42;

  // shared pointers can point to sub-obj
  struct Foo2 {
    int x;
  };
  std::shared_ptr<Foo2> p1 = std::make_shared<Foo2>();
  std::shared_ptr<int> p2(p1, &p1->x);

  // if p1 goes out of scope underlying Foo2 obj will still be alive
}

// sharing with temp ownership:

// weak_ptr: can point to obj owned by instances of shared_ptr while only
// becoming temp owners, this means weak pointers do not alter the obj's
// reference count and therefore do not prevent an obj's deletion 

struct TreeNode{
  std::weak_ptr<TreeNode> parent;
  std::vector< std::shared_ptr<TreeNode> > children;
};

int main(){

 std::shared_ptr<TreeNode> root(new TreeNode); // create as root

 for(size_t i = 0; i < 100; ++i) { // give parent 100 child nodes
   std::shared_ptr<TreeNode> child(new TreeNode);
   root->children.push_back(child);
   child->parent = root;
 }

 root.reset(); //all the childs destroyed
}