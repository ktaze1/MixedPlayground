#include <iostream>
#include <utility>

template <unsigned int n> struct factorial {
  enum { value = n * factorial<n - 1>::value };
};

// factorials can be computed at compile-time

template <> struct factorial<0> {
  enum { value = 1 };
};


constexpr long long factorialBetter(long long n) {
  if (n == 0)
    return 1;
  else
    return n * factorialBetter(n - 1);
}

// for c++17 fold expressions

template <class T, T N, class I = std::make_integer_sequence<T, N>>
struct factorialNew;

template <class T, T N, T... Is>
struct factorialNew<T, N, std::index_sequence<N, Is...>> {
  static constexpr T value = (static_cast<T>(1) * ... * (Is + 1));
};

// iterate over parameter pack

void print_all(std::ostream &os) {
  // base case
}
template <class T, class... Ts>
void print_all(std::ostream &os, T const &first, Ts const &...rest) {
  os << first;
  print_all(os, rest...);
}

// calculating power at compile time

template <class T, T V, T N, class I = std::make_integer_sequence<T, N>>
struct power;


template <class T, T V, T N, T... Is>
struct power<T, V, N, std::integer_sequence<T, Is...>> {
  static constexpr T value =
      (static_cast<T>(1) * ... * (V * static_cast<bool>(Is + 1)));
};


int main() { 
    std::cout << factorial<7>::value << '\n'; 

    std::cout << power<int, 4, 2>::value << '\n';
}