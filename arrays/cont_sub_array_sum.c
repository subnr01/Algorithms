/*
Given an unsorted array of nonnegative integers, find a continous subarray which adds to a given number. 
Examples:
Input: arr[] = {1, 4, 20, 3, 10, 5}, sum = 33
Ouptut: Sum found between indexes 2 and 4

Input: arr[] = {1, 4, 0, 0, 3, 10, 5}, sum = 7
Ouptut: Sum found between indexes 1 and 4

Input: arr[] = {1, 4}, sum = 0 
Output: No subarray found 

There may be more than
one subarrays with sum as the given sum. The following solutions print first
such subarray.  


Solution: Initialize a variable curr_sum as first element.
curr_sum indicates the sum of current subarray. Start from the second element
and add all elements one by one to the curr_sum. If curr_sum becomes equal to
sum, then print the solution. If curr_sum exceeds the sum, then remove trailing
elemnents while curr_sum is greater than sum.

*/

for (i = 1; i <= n; i++)
    {
        // If curr_sum exceeds the sum, then remove the starting elements
        while (curr_sum > sum && start < i-1)
        {
            curr_sum = curr_sum - arr[start];
            start++;
        }
 
        // If curr_sum becomes equal to sum, then return true
        if (curr_sum == sum)
        {
            printf ("Sum found between indexes %d and %d", start, i-1);
            return 1;
        }
 
        // Add this element to curr_sum
        if (i < n)
          curr_sum = curr_sum + arr[i];
    }
