#include <iostream>

// default constructor

class C {
  int i;
  int* is;
public:

    // default constructor
    C(): i{0} // member init list 
    {} // constructor body

    ~C(){ // destructor
        delete[] is;
    }
    
};