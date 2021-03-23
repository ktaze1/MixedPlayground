#include <iostream>
#include <type_traits>
#include <vector>

// func overloading

void print(int num) { std::cout << "This is an int: " << num; }

void print(std::string str) { std::cout << "This is a string: " << str; }

// Operator overloading

template <typename T> T operator+(T lhs, const T &rhs) {
  lhs += rhs;
  return lhs;
}

namespace Example {

template <typename value_t> struct complex {

  value_t x;
  value_t y;

  complex &operator+=(const value_t &x) {
    this->x += x;
    return *this;
  }

  complex &operator+=(const complex &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }

  complex &operator-=(const value_t &x) {
    this->x -= x;
    return *this;
  }
  complex &operator-=(const complex &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }

  complex &operator*=(const value_t &s) {
    this->x *= s;
    this->y *= s;
    return *this;
  }
  complex &operator*=(const complex &other) {
    (*this) = (*this) * other;
    return *this;
  }
  complex &operator/=(const value_t &s) {
    this->x /= s;
    this->y /= s;
    return *this;
  }
  complex &operator/=(const complex &other) {
    (*this) = (*this) / other;
    return *this;
  }

  complex(const value_t &x, const value_t &y) : x{x}, y{y} {} // constructor

  template <typename other_val_t>
  explicit complex(const complex<other_val_t> &other)
      : x{static_cast<const value_t &>(other.x)},
        y{static_cast<const value_t &>(other.y)} {}

  complex &operator=(const complex &) = default;
  complex &operator=(complex &&) = default;
  complex(const complex &) = default;
  complex(complex &&) = default;
  complex() = default;
};

// Absolute value squared
template <typename value_t> value_t absqr(const complex<value_t> &z) {
  return z.x * z.x + z.y * z.y;
}

// operator - (negation)
template <typename value_t>
complex<value_t> operator-(const complex<value_t> &z) {
  return {-z.x, -z.y};
}

// operator +
template <typename left_t, typename right_t>
auto operator+(const complex<left_t> &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a.x + b.x)>> {
  return {a.x + b.x, a.y + b.y};
}

template <typename left_t, typename right_t>
auto operator+(const left_t &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a + b.x)>> {
  return {a + b.x, b.y};
}

template <typename left_t, typename right_t>
auto operator+(const complex<left_t> &a, const right_t &b)
    -> complex<std::decay_t<decltype(a.x + b)>> {
  return {a.x + b, a.y};
}

// operator -
template <typename left_t, typename right_t>
auto operator-(const complex<left_t> &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a.x - b.x)>> {
  return {a.x - b.x, a.y - b.y};
}

template <typename left_t, typename right_t>
auto operator-(const left_t &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a - b.x)>> {
  return {a - b.x, -b.y};
}

template <typename left_t, typename right_t>
auto operator-(const complex<left_t> &a, const right_t &b)
    -> complex<std::decay_t<decltype(a.x - b)>> {
  return {a.x - b, a.y};
}

// operator *
template <typename left_t, typename right_t>
auto operator*(const complex<left_t> &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a.x * b.x)>> {
  return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

template <typename left_t, typename right_t>
auto operator*(const left_t &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a * b.x)>> {
  return {a * b.x, a * b.y};
}

template <typename left_t, typename right_t>
auto operator*(const complex<left_t> &a, const right_t &b)
    -> complex<std::decay_t<decltype(a.x * b)>> {
  return {a.x * b, a.y * b};
}

// operator

template <typename left_t, typename right_t>
auto operator/(const complex<left_t> &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a.x / b.x)>> {
  const auto r = absqr(b);
  return {(a.x * b.x + a.y * b.y) / r, (-a.x * b.y + a.y * b.x) / r};
}
template <typename left_t, typename right_t>
auto operator/(const left_t &a, const complex<right_t> &b)
    -> complex<std::decay_t<decltype(a / b.x)>> {
  const auto s = a / absqr(b);
  return {b.x * s, -b.y * s};
}
template <typename left_t, typename right_t>
auto operator/(const complex<left_t> &a, const right_t &b)
    -> complex<std::decay_t<decltype(a.x / b)>> {
  return {a.x / b, a.y / b};
}

} // namespace Example