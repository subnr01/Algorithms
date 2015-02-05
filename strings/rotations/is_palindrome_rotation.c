

Simple solution:
A Simple Solution is to take the input string, try every possible rotation of it and return true if a rotation is a palindrome. 
If no rotation is palindrome, then return false.
Complexity is O(n2)

Optimised solution:
An Optimized Solution can work in O(n) time. The idea is similar to this post. Following are steps.
1) Let the given string be ‘str’ and length of string be ‘n’. Create a temporary string ‘temp’ which is 
   of size 2n and contains str followed by str again. For example, let str be “aab”, temp would be “aabaab”.
2) Now the problem reduces to find a palindromic substring of length n in str. If there is palindromic substring 
   of length n, then return true, else return false.
We can find whether there is a palindromic substring of size n or not in O(n) time (See Longest palindromic substring)

