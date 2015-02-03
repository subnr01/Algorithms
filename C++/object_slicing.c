What is object slicing?
Object slicing is a concept where additional attributes of a derived class object is sliced to form a base class object.
Object slicing doesn't occur when pointers or references to objects are passed as function arguments since both the pointers are of the same size.
Object slicing will be noticed when pass by value is done for a derived class object for a function accepting base class object.
Object slicing could be prevented by making the base class function pure virtual there by disallowing object creation.
Demonstrate the concept of object slicing

#include <iostream>
using namespace std;

class Base {
        int data1;
        int data2;
    public:
        Base(int a, int b) {
            data1 = a;
            data2 = b;
        }

        virtual void display() {
            cout << "I am Base class" << endl;
        }
};

class Derived : public Base {
        int data3;
    public:
        Derived(int a, int b, int c) : Base(a, b) {
            data3 = c;
        }

        void display() {
            cout << "I am Derived class" << endl;
        }
};

void somefunc ( Base obj )
{
    obj.display();
}

int main()
{
    Base b(10, 20);
    Derived d(100, 200, 300);

    somefunc(b);
    somefunc(d);
}
OUTPUT: 
I am Base class
I am Base class
- See more at: http://www.sourcetricks.com/2008/05/c-object-slicing.html#sthash.neMkM8Iq.dpuf
