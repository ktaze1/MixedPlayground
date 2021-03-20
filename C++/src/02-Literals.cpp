#include <cstddef>
struct S {
private:   
    int x;
public:
    // S& operator=(const S& other) = default;
    S& operator=(const S& other) {
        x = other.x;
        return *this; // this cannot be used in a static member function
    }
};


// ----------------

struct K;
struct T{
    T(const K* k);
    // ...
};

struct K{
    // ...
    T t{this}; // can be used in brace-or-equal-init for non-static data member
};

//-----------------------

// true, false, nullptr are also literals

void f(int* p);

template <class T>
void g(T* p);

void h(std::nullptr_t p); // type of nullptr is nullptr_t

int main(){
    f(nullptr); // ok
    g(nullptr); //error
    h(nullptr); //ok
}