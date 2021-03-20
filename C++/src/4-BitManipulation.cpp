// Remove rightmost bit
#include <type_traits>
#include <bitset>
template <typename T> T rightmostSetBitRemoved(T n) {
  static_assert(std::is_integral<T>::value && !std::is_signed<T>::value,
                "Type should be unsigned!");

  return n & (n - 1);
  // 0bxxxx00 - 0bxxxx011 = 0bxxxx000
}

// set all bits
std::bitset<10> x; 
x.set(); // set all to 1
x.flip(); //flips all bits
x.flip(2); //flips the 3rd rmb


// to be continued