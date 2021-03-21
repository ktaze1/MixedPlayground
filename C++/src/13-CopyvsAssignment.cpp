#include <iostream>
#include <string>

// assignment when you replace data with an already existing obj w/ some other
// obj's data

class Foo{
    public:
    Foo(int data){ //constructor
        this->data = data;
    }

    Foo(const Foo& rhs){ // copy constructor
        data = rhs.data;
    }

    ~Foo(){}; //destructor

    // assignment operator
    Foo& operator=(const Foo& rhs){ // rhs = right hand side
        data = rhs.data;
        return *this;
    }



    int data;
};


int main(){

    Foo foo(2); // constructor called
    Foo foo2(42); 

    foo = foo2; //assignment operator called
    std::cout << foo.data << '\n'; // prints 42

    Foo foo3 = foo2; // copy constructor is called
}