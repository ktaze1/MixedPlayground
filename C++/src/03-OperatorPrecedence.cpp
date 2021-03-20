#include <iostream>

// && has precedence over ||

void test(){
    int a = 1;
std::cout << ++a; // a = 2;
a--;
}