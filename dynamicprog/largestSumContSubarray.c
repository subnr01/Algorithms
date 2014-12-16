
/* 
C program to find largest sum of contigous subarray
using kadane's algorithm

Kadane’s Algorithm:

Initialize:
    max_so_far = 0
    max_ending_here = 0

Loop for each element of the array
  (a) max_ending_here = max_ending_here + a[i]
  (b) if(max_ending_here < 0)
            max_ending_here = 0
  (c) if(max_so_far < max_ending_here)
            max_so_far = max_ending_here
return max_so_far



*/

int maxSubArraySum(int a[], int size)
{
   int max_so_far = 0, max_ending_here = 0;
   int i;
   for(i = 0; i < size; i++)
   {
     max_ending_here = max_ending_here + a[i];
    
     if(max_ending_here < 0)
        max_ending_here = 0;


     else if(max_so_far < max_ending_here)
        max_so_far = max_ending_here;
    
    }
    return max_so_far;
} 


/*
The algorithm does not work 
if all the elements in the
array are negative numbers

*/


