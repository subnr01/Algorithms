/*

Write an efficient C program to find smallest and second smallest element in an array


*/

Solution:
Steps:
1.	Have two variables, first=second=INT_MAX
2.	Have the max value first= max, second will be lesser than max
for ( i = 0 to size) {
   if ( array[i] < first) {
	second = first;
	first = array[i];
   }
   else if (array[i] < second) {
	second = array[i];
   }}



   