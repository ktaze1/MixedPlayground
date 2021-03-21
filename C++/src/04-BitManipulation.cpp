// Remove rightmost bit
#include <bitset>
#include <type_traits>
#include <iostream>

template <typename T> T rightmostSetBitRemoved(T n) {
  static_assert(std::is_integral<T>::value && !std::is_signed<T>::value,
                "Type should be unsigned!");

  return n & (n - 1);
  // 0bxxxx00 - 0bxxxx011 = 0bxxxx000
}

// set all bits
void setBits() {
  std::bitset<10> x;
  x.set();   // set all to 1
  x.set(2, true); // set nth to x
  x.flip();  // flips all bits
  x.flip(2); // flips the 3rd rmb
}

// small to capital letters with bit manipulation

const void setCharToCapital(){
  char op1 = 'a'; //        01 1 00001
  int mask = 0xDF; //mask = 11 0 11111

  std::cout << (op1 & mask); // A = 01000001
}