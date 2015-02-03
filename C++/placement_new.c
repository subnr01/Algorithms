What is placement new in C++?
In some scenarios it becomes necessary to place objects at specified locations in memory. Placement new solves this problem.
For example, there could be predefined memory pools in which certain objects need to be placed on creation.
Placement new is achieved by overloading the new operator which takes more than one argument apart from the default size_t argument.
Demonstrate the usage of placement new

#include <iostream>
using namespace std;

class MyClass {
   
   public:

    // Placement new operator
    void* operator new (size_t sz, void* v) {
        cout << "Placement new invoked" << endl;
        return v;
    }

    ~MyClass() {
        // Cleanup
    }
};

int main()
{
    // Create a buffer to store the object
    int buffer[16];
    cout << "Starting address of my buffer = " << &buffer << endl;

    // Create the object. Use placement new
    MyClass* obj = new (buffer) MyClass();
    cout << "Location of my object = " << obj << endl;

    // Don't delete object created with placement delete
    // Call the destructor explicitly
    obj->~MyClass();
}
- See more at: http://www.sourcetricks.com/2008/05/c-placement-new.html#sthash.EMoJK7bm.dpuf
