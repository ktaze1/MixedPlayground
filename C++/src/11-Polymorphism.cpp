#include <iostream>

// classical example

class Shape {
public:
  virtual ~Shape() = default;
  virtual double get_surface()  = 0; // pure virtual
  virtual void describe_object()  { std::cout << "this is a shape \n"; }

  double get_doubled_surface() { return 2 * get_surface(); }
};

// Derived Class

class Point {};

class Square : public Shape {
  Point top_left;
  double side_length;

public:
  Square(const Point &top_left, double side)
      : top_left(top_left), side_length(side_length) {}

    double get_surface() override { return side_length * side_length; }
    void describe_object() override {
        std::cout << "this is a square";
    }
};