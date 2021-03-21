class Foo {
public:
  int &GetBar(
      /*some arguments*/) { // isn't const and returns non-const reference
    // some calculation
    return bar;
  }

  const int &
      GetBar(/*some arguments*/) const { // is const and returns const reference
    // some calculations
    return bar;
  }

private:
  int bar;
};

// better version without duplication:

class Student {
public:
  char &GetScore(bool midterm) {
    return const_cast<char &>(
        const_cast<const Student *>(this)->GetScore(midterm));
  }

  const char &GetScore(bool midterm) const {
    if (midterm)
      return midtermScore;
    else
      return finalScore;
  }

private:
  char midtermScore;
  char finalScore;
};

int main() {

  Student a; // non-const

  a.GetScore(true) = 'B';
  a.GetScore(false) = 'A';

  const Student b(a);
  // b.GetScore(true) = 'C'; gives error because it return const reference
}

// Const member functions

// if marked const, this tells compiler function will not modify the object
class ConstMemberClass {
private:
  int age;

public:
  int calcAge() const { return age; }
  void setAge(int newAge) { age = newAge; }
};


// const local vars

void constLocalVariable(){
    const int a = 15;
    // a = 12; Nope
    // a++; nope

    //int &b = a; nope b isn't const
    const int &c = a; // OK

    //same with pointers
    const int *e = &a; // e is a pointer to const
}

//const pointers

void constPointers(){
    int a = 0, b = 2;

    const int* pA = &a; //pointer to const, can't change a

    int* const pB = &a; // const pointer. can change a, can't change the pointer itself

    const int* const pC = &a; //const pointer-to-const
}