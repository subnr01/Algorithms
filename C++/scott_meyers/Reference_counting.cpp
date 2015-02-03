/******************************************************************************
 *                                                                             *
 *        Code from Item 29 ("Reference Counting") of MORE EFFECTIVE C++       *
 *                                                                             *
 *                               Scott Meyers                                  *   
 *                                                                             *
 *            Copyright 1996 (c) Addison-Wesley Publishing Company             *
 *       You are free to use this code for non-commercial purposes only.       *
 *                                                                             *
 * This page contains the code for the classes and class templates making up   *
 * the Reference Counting Item of More Effective C++.  To use this code,       *
 * either copy this page and paste it into a C++ source file or save the       *
 * entire page as text into a C++ source file.  Don't save the HTML source     *
 * and expect that to compile :-)                                              *
 *                                                                             *
 * Each class or template in this file follows a block comment that shows the  *
 * corresponding pages in the book.  This page also contains a main function   *
 * that performs a VERY limited test of the code in this file.  You can        *
 * compile the code in this file as a stand-alone program, and you should get  *
 * this output:                                                                *
 *                                                                             *
 *     String with no changes.                                                 *
 *     String with    changes.                                                 *
 *     10                                                                      *
 *     -1                                                                      *
 *                                                                             *
 * The code here reflects all changes made to date in response to bug reports  *
 * from readers of the book.  (To see a complete list of known bugs in More    *
 * Effective C++, as well as whether they've been fixed yet, visit the         *
 * More Effective C++ Errata List.)  If you find any additional bugs, please   *
 * send them to me.                                                            *
 ******************************************************************************/
 #include <iostream>      // The iostream facilities are not used in the classes
                          // in this file, but they are used in the code that 
                          // tests the classes.
 
 #include <cstring>       // This includes the C string functions, e.g.,
                          // strlen, strcpy, etc.  They are used in the
                          // implementation of class String::StringValue.
 
 // The following is for compilers that don't support bool.  Uncomment these
 // lines if your compilers lack bool support.  For details on this emulation
 // of bool, see More Effective C++, pp. 3-4.
 // typedef int bool;
 // const bool false = 0;
 // const bool true = 1;
 
 /******************************************************************************
 *                       Class RCObject (from pp. 204-205)                     *
 ******************************************************************************/
 class RCObject {                       // base class for reference-
 public:                                // counted objects
   void addReference();
   void removeReference();
   void markUnshareable();
   bool isShareable() const;
   bool isShared() const;
 
 protected:
   RCObject();
   RCObject(const RCObject& rhs);
   RCObject& operator=(const RCObject& rhs);
   virtual ~RCObject() = 0;
 
 private:
   int refCount;
   bool shareable;
 };
 
 RCObject::RCObject()
 : refCount(0), shareable(true) {}
 
 RCObject::RCObject(const RCObject&)
 : refCount(0), shareable(true) {}
 
 RCObject& RCObject::operator=(const RCObject&)
 {
   return *this;
 }  
 
 RCObject::~RCObject() {}
 
 void RCObject::addReference() 
 {
   ++refCount;
 }
 
 void RCObject::removeReference()
 {
   if (--refCount == 0) delete this;
 }
 
 void RCObject::markUnshareable()
 {
   shareable = false;
 }
 
 bool RCObject::isShareable() const
 {
   return shareable;
 }
 
 bool RCObject::isShared() const
 {
   return refCount > 1;
 }  
 
 
 /******************************************************************************
 *                 Template Class RCPtr (from pp. 203, 206)                    *
 ******************************************************************************/
 template<class T>                      // template class for smart
 class RCPtr {                          // pointers-to-T objects; T
 public:                                // must support the RCObject interface
   RCPtr(T* realPtr = 0);
   RCPtr(const RCPtr& rhs);
   ~RCPtr();
   RCPtr& operator=(const RCPtr& rhs);                     
   T* operator->() const;
   T& operator*() const;
 
 private:
   T *pointee;
   void init();
 };
 
 template<class T>
 void RCPtr<T>::init()
 {
   if (pointee == 0) return;
   
   if (pointee->isShareable() == false) {
     pointee = new T(*pointee);
   }
   
   pointee->addReference();
 }
 
 template<class T>
 RCPtr<T>::RCPtr(T* realPtr)
 : pointee(realPtr)
 {
   init();
 }
 
 template<class T>
 RCPtr<T>::RCPtr(const RCPtr& rhs)
 : pointee(rhs.pointee)
 { 
   init();
 }
 
 template<class T>
 RCPtr<T>::~RCPtr()
 {
   if (pointee) pointee->removeReference();
 }
 
 template<class T>
 RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
 {
   if (pointee != rhs.pointee) {                   // this code was modified
     T *oldPointee = pointee;                      // for the book's 10th
                                                   // printing
     pointee = rhs.pointee;
     init(); 
 
     if (oldPointee) oldPointee->removeReference();                
   }
   
   return *this;
 }
 
 template<class T>
 T* RCPtr<T>::operator->() const 
 {
   return pointee;
 }
 
 template<class T>
 T& RCPtr<T>::operator*() const
 {
   return *pointee;
 }
 
 
 /******************************************************************************
 *           Classes String and StringValue (from pp. 204, 206-207)            *
 ******************************************************************************/
 class String {                          // class to be used by
 public:                                 // application developers
   String(const char *value = "");
 
   char operator[](int index) const;       
   char& operator[](int index);
 
 private:
   // class representing string values
   struct StringValue: public RCObject {
     char *data;
  
     StringValue(const char *initValue);
     StringValue(const StringValue& rhs);
     void init(const char *initValue);
     ~StringValue();
   };
 
   RCPtr<StringValue> value;                       
 
   // This function is not in the book, but it's convenient for testing the
   // class -- see below.
   friend std::ostream& operator<<(std::ostream& stream, const String& string);
 };
 
 void String::StringValue::init(const char *initValue)
 {
   using namespace std;
 
   data = new char[strlen(initValue) + 1];
   strcpy(data, initValue);
 }
 
 String::StringValue::StringValue(const char *initValue)
 { 
   init(initValue);
 }
 
 String::StringValue::StringValue(const StringValue& rhs)
 {
   init(rhs.data);
 }
 
 String::StringValue::~StringValue()
 {
   delete [] data;
 }
 
 
 String::String(const char *initValue)
 : value(new StringValue(initValue)) {}
 
 char String::operator[](int index) const
 {
   return value->data[index];
 }
 
 char& String::operator[](int index)
 { 
   if (value->isShared()) {      
     value = new StringValue(value->data);
   }
 
   value->markUnshareable();
 
   return value->data[index];
 }
 
 std::ostream& operator<<(std::ostream& stream, const String& string)
 {
   return stream << string.value->data;
 }
 
 
 /******************************************************************************
 *                  Template Class RCIPtr (from pp. 209-210)                   *
 *                                                                             *
 * The code for RCIPtr has changed over the years in response to errors        *
 * both in the original source code as well as in the subsequent fixes.  You   *
 * can find a complete list of changes at the More Effective C++ errata page.  *
 * The code here is accurate as of the 13th printing of the book.              *
 ******************************************************************************/
 template<class T>
 class RCIPtr {
 public:
   RCIPtr(T* realPtr = 0);
   RCIPtr(const RCIPtr& rhs);
   ~RCIPtr();
   RCIPtr& operator=(const RCIPtr& rhs);
 
   T* operator->() const;
   T& operator*() const;
 
   RCObject& getRCObject()               // give clients access to
   { return *counter; }                  // isShared, etc.
 
 private:
   struct CountHolder: public RCObject {
     ~CountHolder() { delete pointee; }
     T *pointee;
   };
 
   CountHolder *counter;
   void init();
 };
 
 template<class T>
 void RCIPtr<T>::init()
 {
   if (counter->isShareable() == false) {
     T *oldValue = counter->pointee;
     counter = new CountHolder;
     counter->pointee = oldValue ? new T(*oldValue) : 0;
   } 
 
   counter->addReference();
 }
 
 template<class T>
 RCIPtr<T>::RCIPtr(T* realPtr)
 : counter(new CountHolder)
 { 
   counter->pointee = realPtr;
   init();
 }
 
 template<class T>
 RCIPtr<T>::RCIPtr(const RCIPtr& rhs)
 : counter(rhs.counter)
 { init(); }
 
 template<class T>
 RCIPtr<T>::~RCIPtr()
 { counter->removeReference(); }
 
 template<class T>
 RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
 {
   if (counter != rhs.counter) {         
     counter->removeReference();     
     counter = rhs.counter;
     init();
   }
   return *this;
 }
 
 template<class T>
 T* RCIPtr<T>::operator->() const
 { return counter->pointee; }
 
 template<class T>
 T& RCIPtr<T>::operator*() const
 { return *(counter->pointee); }
 
 
 /******************************************************************************
 *                          Class Widget (from p. 210)                         *
 *                                                                             *
 * This class is the same as that in the book, but I've added an               *
 * implementation so that RCIPtr can be tested.                                *
 ******************************************************************************/
 class Widget {
 public:
   Widget(int size): value(size) {}
   Widget(const Widget& rhs): value(rhs.value) {}
   ~Widget() {}
 
   Widget& operator=(const Widget& rhs)
   {
     value = rhs.value;
     return *this; 
   }
 
   void doThis()
   { value = -1; }
 
   int showThat() const
   { return value; }
   
 private:
   int value;
 };
 
 
 /******************************************************************************
 *                         Class RCWidget (from p. 210)                        *
 *                                                                             *
 * I modified this class for the 13th printing of the book.  For details on    *
 * why, consult the erratum affecting pages 209, 210, and 316 that was fixed   *
 * on 7/15/02 in the book's errata list.                                       *
 ******************************************************************************/
 class RCWidget {
 public:
   RCWidget(int size)
   : value(new Widget(size)) {}
 
   void doThis()
   {
     if (value.getRCObject().isShared()) {         // do COW if 
       value = new Widget(*value);                 // Widget is shared
     }
     value->doThis();
   }
 
   int showThat() const
   { return value->showThat(); }
 
 private:
   RCIPtr<Widget> value;
 };
 
 
 /******************************************************************************
 * Functions to perform VERY simple test of the above.                         *
 ******************************************************************************/  
 void testRCPtr()
 {
   String s1 = "String with no changes.";
   String s2(s1);
   
   s2[12] = s2[13] = ' ';
   
   std::cout << s1 << '\n';      // prints "String with no changes."
   std::cout << s2 << '\n';      // prints "String with    changes."
 }
 
 void testRCIPtr()
 {
   RCWidget w1(10);
   RCWidget w2(w1);
 
   w2.doThis();
   
   std::cout << w1.showThat() << '\n';       // prints 10
   std::cout << w2.showThat() << '\n';       // prints -1
 }
 
 int main()
 {
   testRCPtr();
   testRCIPtr();
 
   return 0;
 }
