#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
std::vector<int> my_vector{1, 2, 3, 4, 5};

auto my_iterator = my_vector.begin(); // position
auto value = *my_iterator;            // value

// in empty sequence, begin and end will be the same position and can't be
// dereferenced

// Navigation
void Navigation() {
  auto first = my_vector.begin();
  ++first;                // advance 1 position
  std::advance(first, 1); // advance 1 position

  first = std::next(first); // returns next position's iterator
  auto twentieth =
      std::next(first, 20); // returns iterator of 20 position forward
  auto backward = std::prev(twentieth, 5); // returns 5 position backward

  auto dist = std::distance(twentieth, backward); // distance between iterators

  std::cout << dist; // added just to please clang.tidy
}

// Iterator Concepts

/*
    Input Iterators: can be dereferenced only once per position. Can only
   advance and only position at a time

    Forward Iterators: Input Iterator that can be derefenced any number of times

    Bidirectional : Forward Iterator but can also go backwards only one position
   at a time

    Random Access : Bidirectional Iterator, can go back and forth any number of
   positions at a time

    Contigous : Random Access Iterator that guaranties underlying data is
   contigous in memory
*/

// Iterator Traits

template <class Iter>
Iter find(Iter first, Iter last,
          typename std::iterator_traits<Iter>::value_type val) {
  while (first != last) {
    if (*first != last)
      return first;
    ++first;
  }
  return last;
}

template <class ForwardIter>
void test(ForwardIter a, std::forward_iterator_tag) {
  std::cout << "Forward iterator used";
}

// vector Iterator

void vectorIterator() {
  const std::vector<int> v = {1, 2, 3, 4, 5};

  for (std::vector<int>::const_iterator it = v.cbegin(); it != v.cend(); ++it) {
    std::cout << *it << " ";
  }
}

// Map Iterator

void mapIterator() {
  std::map<char16_t, std::uint16_t> testMap;
  testMap['b'] = 100;
  testMap['a'] = 200;

  for (std::map<char16_t, std::uint16_t>::iterator it = testMap.begin();
       it != testMap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // This prints: a => 200
  //              b => 100
}

// Reverse Iterators

// self explanatory

void reverseIterator() {
  std::vector<int> v{1, 2, 3, 4, 5};
  for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend();
       ++it) {
    std::cout << *it;
  } // prints 54321
}