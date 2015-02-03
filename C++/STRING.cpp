#ifndef STRING_H
#define STRING_H

#include <iostream.h>
#include <fstream.h>

class String
{
  friend int operator==(char*,const String&);
  friend int operator==(const String&,const String&);
  friend int operator==(const String&,char*);
  friend ostream& operator<<(ostream&,String&);
  friend istream& operator>>(istream&,String&);
public:
  //  constructors and destructor
  String() : len(0), theChars(NULL) { }
  String(char *);
  String(String&);
  ~String();
  //  accessors
  int length() const { return len; }
  int at(int, char&) const;
  int find(char) const;
  int substring(String&,int,int) const;
  String operator+(const String&) const;
  //  mutators
  String& operator=(const String&);
private:
  char *theChars;
  int len;
};

#endif

File String.C:


#include <iostream.h>
#include <fstream.h>
#include "String.h"

//  constructor that initializes from an array of char
String::String(char *init)
{
//  find the length of the initializing array (look
//  for null byte)
   len = 0;
   while (init[len] != '\0')
      len++;

//  allocate space and copy chars into invoking obj
   theChars = new char[len];
   for (int i = 0 ; i < len ; i++)
      theChars[i] = init[i];
}

//  copy constructor
String::String(String& old)
{
//  check whether we are copying the empty string
   len = old.len;
   if (len == 0)
      theChars = NULL;

//  if not, copy the chars into the new array and
//  copy the length
   else
   {
      theChars = new char[len];
      for (int i = 0 ; i < len ; i++)
         theChars[i] = old.theChars[i];
   }
}

//  destructor
String::~String()
{
   if (len > 0)
      delete [] theChars;
}

//  overloaded << operator to print a String
ostream& operator<<(ostream& out, String& prt)
{
   for (int i = 0 ; i < prt.len ; i++)
      out << prt.theChars[i];
   return out;
}

//  concatenate the parm and the invoking String and
//  return the resulting String
String String::operator+(const String& two) const
{
   String result;
   int i;

//  if both Strings are empty, result is empty too
   if (len == 0 && two.len == 0)
   {
      result.len = 0;
      result.theChars = NULL;
   }
   else
   {

//  find length of the result and get space for it
      result.len = len + two.len;
      result.theChars = new char[result.len];

//  copy the invoking String into the new String
      for (i = 0 ; i < len ; i++)
         result.theChars[i] = theChars[i];

//  copy the parm at the end of the new String
      int j = 0;
      while (j < two.len)
      {
         result.theChars[i] = two.theChars[j];
         i++;
         j++;
      }
   }
   return result;
}

//  return the character at the given position in the
//  parm ch. if position is invalid return false;
//  otherwise return true
int String::at(int position, char& ch) const
{
   int returnCode = 0;
   if (position >= 0 && position < len)
   {
      ch = theChars[position];
      returnCode = 1;
   }
   return returnCode;
}

//  test whether two Strings are equal; return true if
//  so, false if not
int operator==(const String &one, const String& two)
{
   int ret = 1;
   if (one.len != two.len)
      ret = 0;
   else
      for (int i = 0 ; i < one.len && ret == 1 ; i++)
         if (one.theChars[i] != two.theChars[i])
            ret = 0;
  return ret;
}

//  test whether a String object contains the same
//  string as an array of char
int operator==(const String& one, char *chstr)
{
   int equal = 1;
   int stlen = 0;

//  find the length of the array of characters
   while (chstr[stlen] != '\0')
      stlen++;

//  if the lengths are equal, check whether all the
//  characters are equal
   if (one.len == stlen)
      for (int i = 0 ; i < one.len ; i++)
      {
         if (one.theChars[i] != chstr[i])
            equal = 0;
      }
   else
      equal = 0;
  return equal;
}

//  test whether a String object contains the same
//  string as an array of char
int operator==(char *chstr,const String& one)
{
   int equal = 1;
   int stlen = 0;

//  find the length of the array of characters
   while (chstr[stlen] != '\0')
      stlen++;

//  if the lengths are equal, check whether all the
//  characters are equal
   if (one.len == stlen)
      for (int i = 0 ; i < one.len ; i++)
      {
         if (one.theChars[i] != chstr[i])
            equal = 0;
      }
   else
      equal = 0;
   return equal;
}

//  copy the parm into the invoking object
String& String::operator=(const String& two)
{
   if (theChars != 0)
      delete [] theChars;
   len = two.len;
   theChars = new char[len];
   for (int i = 0 ; i < len ; i++)
      theChars[i] = two.theChars[i];
   return *this;
}

File strtest.C:

#include <iostream.h>
#include <fstream.h>
#include "String.h"


//  test the String class

int main()
{
   String first;
   String second;
   String third;
   int len;
   int end;
   int ok;
   char ch;

   cout << "Enter a string: \n";
   cin >> first;
   len = first.length();
   end = len / 2;
   ok = first.substring(second,0,end);
   ok = first.substring(third,end+1,len-1);
   first = third + second;
   cout << "\nNew version of string: ";
   cout << endl << first << endl << endl;
   ok = first.at(4,ch);
   if (ok)
      cout << "The 5th char of the new string is "
                             << ch << endl;
   else
      cout << "The new string has less than 5 char\n";
   ok = first.find('a');
   if (ok != -1)
      cout << "The first place a was found is loc "
                             << ok << endl;
   else
      cout << "There was no a in the new string\n";
   cout << endl;
   if (first == "how about it")
      cout << "The strings match\n";
   else
      cout << "The strings don't match\n";
}

To Compile and Execute:

>g++ String.C strtest.C
>a.out

Output:

Enter a string:
we wouldn't have to walk to the store

New version of string:
walk to the storewe wouldn't have to

The 5th char of the new string is k
The first place a was found is in loc 2

The strings don't match

