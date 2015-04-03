/*
Write a program to print all the LEADERS in the array. An element is leader if
it is greater than all the elements to its right side. And the rightmost
element is always a leader. For example int the array {16, 17, 4, 3, 5, 2},
leaders are 17, 5 and 2.

*/

Solution:
Scan the array from right to left and keep track of the maximum till now. When max value changes, print the old max.

