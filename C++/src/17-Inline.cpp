#include <iostream>

inline int add(int x, int y){
    return x+y;
}

int main(){
    int a = 1, b= 2;
    int c = add(a,b); // this is equivalent to int c = a+b;

    std::cout << c;
}