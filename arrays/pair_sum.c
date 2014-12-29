/*
Given an array A[] and a number x, 
check for pair in A[] with sum as x

*/


/*
 Solution 1
1.	Sort the array in increasing order.
2.	Have one index in the front and one at the rear and compute the sum.
3.	If sum < x front++;
4.	If sum > x rear--;
5.	If front==rear exit

Solution 2
If hash map is used then if a[i] – x is set then we have found a pair.

*/

while(l < r)
    {
         if(A[l] + A[r] == sum)
              return 1; 
         else if(A[l] + A[r] < sum)
              l++;
         else // A[i] + A[j] > sum
              r--;
    }    


