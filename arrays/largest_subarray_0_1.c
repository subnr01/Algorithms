/*

Given an array containing only 0s and 1s, find the largest subarray 
which contain equal no of 0s and 1s. Expected time complexity is O(n). 

Examples:
Input: arr[] = {1, 0, 1, 1, 1, 0, 0}
Output: 1 to 6 (Starting and Ending indexes of output subarray)

Input: arr[] = {1, 1, 1, 1}
Output: No such subarray

Input: arr[] = {0, 0, 1, 1, 0}
Output: 0 to 3 Or 1 to 4

Method 2 (Tricky)
Following is a solution that uses O(n) extra space and solves the problem in O(n) time complexity.
Let input array be arr[] of size n and maxsize be the size of output subarray.
1) Consider all 0 values as -1. The problem now reduces to find out the maximum length subarray with sum = 0.
2) Create a temporary array sumleft[] of size n. Store the sum of all elements from arr[0] to arr[i] in sumleft[i]. 
This can be done in O(n) time.
3) There are two cases, the output subarray may start from 0th index or may start from some other index.
We will return the max of the values obtained by two cases.
4) To find the maximum length subarray starting from 0th index, scan the sumleft[] and find the maximum i 
where sumleft[i] = 0.
5) Now, we need to find the subarray where subarray sum is 0 and start index is not 0. This problem is 
equivalent to finding two indexes i & j in sumleft[] such that sumleft[i] = sumleft[j] and j-i is maximum. 
To solve this, we can create a hash table with size = max-min+1 where min is the minimum value in the 
sumleft[] and max is the maximum value in the sumleft[]. The idea is to hash the leftmost occurrences of all different values in sumleft[]. The size of hash is chosen as max-min+1 because there can be these many different possible values in sumleft[]. Initialize all values in hash as -1
6) To fill and use hash[], traverse sumleft[] from 0 to n-1. If a value is not present in hash[], 
then store its index in hash. If the value is present, then calculate the difference of current index 
of sumleft[] and previously stored value in hash[]. If this difference is more than maxsize, then update the maxsize.
7) To handle corner cases (all 1s and all 0s), we initialize maxsize as -1. If the maxsize remains -1,
then print there is no such subarray.
*/

int findSubArray(int arr[], int n)
{
    int maxsize = -1, startindex;  // variables to store result values
  
    // Create an auxiliary array sunmleft[]. sumleft[i] will be sum of array 
    // elements from arr[0] to arr[i]
    int sumleft[n];
    int min, max; // For min and max values in sumleft[]
    int i;
  
    // Fill sumleft array and get min and max values in it. 
    // Consider 0 values in arr[] as -1
    sumleft[0] = ((arr[0] == 0)? -1: 1);
    min = arr[0]; max = arr[0];
    for (i=1; i<n; i++)
    {      
        sumleft[i] = sumleft[i-1] + ((arr[i] == 0)? -1: 1);
        if (sumleft[i] < min)
            min = sumleft[i];
        if (sumleft[i] > max)
            max = sumleft[i];
    }
  
    // Now calculate the max value of j - i such that sumleft[i] = sumleft[j].   
    // The idea is to create a hash table to store indexes of all visited values.   
    // If you see a value again, that it is a case of sumleft[i] = sumleft[j]. Check 
    // if this j-i is more than maxsize. 
    // The optimum size of hash will be max-min+1 as these many different values 
    // of sumleft[i] are possible. Since we use optimum size, we need to shift
    // all values in sumleft[] by min before using them as an index in hash[].
    int hash[max-min+1];
  
    // Initialize hash table
    for (i=0; i<max-min+1; i++)
        hash[i] = -1;
  
    for (i=0; i<n; i++)
    {
        // Case 1: when the subarray starts from index 0
        if (sumleft[i] == 0)
        {
           maxsize = i+1;
           startindex = 0;
        }
  
        // Case 2: fill hash table value. If already filled, then use it
        if (hash[sumleft[i]-min] == -1)
            hash[sumleft[i]-min] = i;
        else
        {
            if ( (i - hash[sumleft[i]-min]) > maxsize )
            {
                maxsize = i - hash[sumleft[i]-min];
                startindex = hash[sumleft[i]-min] + 1;
            }
        }
    }
    if ( maxsize == -1 )
        printf("No such subarray");
    else
        printf("%d to %d", startindex, startindex+maxsize-1);
  
    return maxsize;
}

