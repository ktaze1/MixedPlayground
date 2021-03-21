#include "catch.hpp"
#include <vector>
#include <iostream>
// range-based for

void rangeFor() {
  std::vector<float> v = {0.4f, 12.5f, 16.234234f};

  for (auto val : v)
    std::cout << val << '\n';


  //you can also reference
  for(float &val: v)
   std::cout << val << " ";
}

void forLoop(){
    for(;; /*init statements; condition; iteration execution*/){
        //if empty this is infinite
    }
}

int main(int argc, char **argv){
    rangeFor();
}