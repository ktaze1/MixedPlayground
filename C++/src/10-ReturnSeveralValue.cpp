#include <tuple>
#include <utility>
//there are many ways

std::tuple<int, int, int, int> foo(int a, int b) { // c++11
    return std::make_tuple(a+b, a-b, a*b, a/b);
}

std::tuple<int, int, int, int> fooBetter(int a, int b) { // c++17
    return {a+b, a-b, a*b, a/b};
}

// for only two values use pair

std::pair<int, int> fooPair(int a, int b){
    return {a+b, a-b};
}


// make vector and fill with it