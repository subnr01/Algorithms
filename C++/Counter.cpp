Sample Program: Counter Classes with Inheritance

//////////////////////////////////////////////////////////////////////
//
//  Counter keeps a count which can be initialized to zero or
//  another positive integer value -- member functions allow
//  the count to be incremented and return the current value
//  of the counter
//
//////////////////////////////////////////////////////////////////////
class Counter
{
public:
   Counter()       { count = 0; }
   Counter(int c)  { count = c; }
   int get_count() { return count; }
   Counter& operator++() { count++; return *this; }
protected:
   int count;
};

//////////////////////////////////////////////////////////////////////
//
//  class CountUD is derived from Counter -- it adds the ability to
//  decrement the counter
//
//////////////////////////////////////////////////////////////////////
class CountUD : public Counter
{
public:
   CountUD& operator--();
};

//////////////////////////////////////////////////////////////////////
//
//  prefix decrement operator for CountUD -- decrements the counter;
//  makes sure that counter wasn't already zero
//
//////////////////////////////////////////////////////////////////////
CountUD& CountUD::operator--()
{
   if (count != 0)
      count--;
   return *this;
}

//////////////////////////////////////////////////////////////////////
//
//  client code
//
//////////////////////////////////////////////////////////////////////
#include <iostream.h>
int main()
{
   CountUD ct1;
   Counter c;

   ++c;
   cout << endl << "c = " << c.get_count();

   cout << endl << "ct1 = " << ct1.get_count();
   ++(++ct1);
   cout << endl << "ct1 = " << (++ct1).get_count();
   --ct1;
   cout << endl << "ct1 = " << (--ct1).get_count();

}

