/*
What is RTTI?
RTTI stands for Run-time Type Identification.
RTTI is useful in applications in which the type of objects is known only at run-time.
Use of RTTI should be minimized in programs and wherever possible static type system should be used.
RTTI allows programs that manipulate objects or references to base classes to retrieve the actual derived types to which they point to at run-time.
Two operators are provided in C++ for RTTI.
dynamic_cast operator. The dynamic_cast operator can be used to convert a pointer that refers to an object of class type to a pointer to a class in the same hierarchy. On failure to cast the dynamic_cast operator returns 0.
typeid operator. The typeid operator allows the program to check what type an expression is. When a program manipulates an object through a pointer or a reference to a base class, the program needs to find out the actual type of the object manipulated.
The operand for both dynamic_cast and typeid should be a class with one or more virtual functions.
Demonstrate the RTTI mechanisms in C++
*/
#include <iostream>
#include <typeinfo> // Header for typeid operator
using namespace std;

// Base class
class MyBase {
  public:
    virtual void Print() {
        cout << "Base class" << endl;
    };
};

// Derived class
class MyDerived : public MyBase {
  public:
    void Print() {
        cout << "Derived class" << endl;
    };
};

int main()
{
    // Using typeid on built-in types types for RTTI
    cout << typeid(100).name() << endl;    
    cout << typeid(100.1).name() << endl;

    // Using typeid on custom types for RTTI
    MyBase* b1 = new MyBase();
    MyBase* d1 = new MyDerived();

    MyBase* ptr1;
    ptr1 = d1;

    cout << typeid(*b1).name() << endl;
    cout << typeid(*d1).name() << endl;
    cout << typeid(*ptr1).name() << endl;

    if ( typeid(*ptr1) == typeid(MyDerived) ) {
    cout << "Ptr has MyDerived object" << endl;
    }

    // Using dynamic_cast for RTTI
    MyDerived* ptr2 = dynamic_cast<MyDerived*> ( d1 );
    if ( ptr2 ) {
    cout << "Ptr has MyDerived object" << endl;
    }
}
- See more at: http://www.sourcetricks.com/2008/06/c-rtti.html#sthash.bZV6ITJK.dpuf
