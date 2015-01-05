
/*

Write an efficient program for printing k largest elements in an array. 
Elements in array can be in any order. 
For example, if given array is [1, 23, 12, 9, 30, 2, 50] and 
you are asked for the largest 3 elements i.e., k = 3 then your program should print 50, 30 and 23.


*/

Elements in array can be in any order. 
For example, if given array is [1, 23, 12, 9, 30, 2, 50] 
and you are asked for the largest 3 elements i.e., k = 3 
then your program should print 50, 30 and 23.

Solution:

Method 3(Use Sorting)  Complexity nlogn
1) Sort the elements in descending order in O(nLogn) 
2) Print the first k numbers of the sorted array O(k).


Method 4 (Use Max Heap) Complexity: O(n + klogn)
1) Build a Max Heap tree in O(n) 
2) Use Extract Max k times to get k maximum elements from the Max Heap O(klogn)
