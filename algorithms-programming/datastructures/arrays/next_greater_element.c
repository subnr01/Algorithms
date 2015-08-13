/*

Given an array, print the Next Greater Element (NGE) for every element. The Next greater Element for an element x is the first greater element on the right side of x in array. Elements for which no greater element exist, consider next greater element as -1. 

Examples: 
a) For any array, rightmost element always has next greater element as -1.
b) For an array which is sorted in decreasing order, all elements have next greater element as -1. 
c) For the input array [4, 5, 2, 25}, the next greater elements for each element are as follows. 
Element NGE 
4 --> 5 
5 --> 25 
2 --> 25 
25 --> -1 
d) For the input array [13, 7, 6, 12}, the next greater elements for each element are as follows. 
Element NGE 
13 --> -1 
7 --> 12 
6 --> 12 
12 --> -1

*/

/*
Solution
1) Push the first element to stack. 

2) Pick rest of the elements one by one and follow following steps in loop. 
....a) Mark the current element as next. 
....b) If stack is not empty, then pop an element from stack and compare it with next. 
....c) If next is greater than the popped element, then next is the next greater element for 
	   the popped element. 
....d) Keep poppoing from the stack while the popped element is smaller than next. next becomes the 
       next greater element for all such popped elements 
....g) If next is smaller than the popped element, then push the popped element back. 

3) After the loop in step 2 is over, pop all the elements from stack and print -1 as next element for them.
*/

