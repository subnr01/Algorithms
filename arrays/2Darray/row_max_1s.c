/*

Given a boolean 2D array, where each row is sorted. 
Find the row with the maximum number of 1s.


Example
Input matrix
0 1 1 1
0 0 1 1
1 1 1 1  // this row has maximum 1s
0 0 0 0

Output: 2
Since each row is sorted, we can use Binary Search to count of 1s in each row.
 We find the index of first instance of 1 in each row. The count of 1s will be 
 equal to total number of columns minus the index of first 

 */

 int first(bool arr[], int low, int high)
{
  if(high >= low)
  {
    // get the middle index  
    int mid = low + (high - low)/2; 
 
    // check if the element at middle index is first 1
    if ( ( mid == 0 || arr[mid-1] == 0) && arr[mid] == 1)
      return mid;
 
    // if the element is 0, recur for right side
    else if (arr[mid] == 0)
      return first(arr, (mid + 1), high);
 
    else // If element is not first 1, recur for left side
      return first(arr, low, (mid -1));
  }
  return -1;
}


/*

Following method works in O(m+n) time complexity in worst case.
Step1: Get the index of first (or leftmost) 1 in the first row.
Step2: Do following for every row after the first row
…IF the element on left of previous leftmost 1 is 0, ignore this row.
…ELSE Move left until a 0 is found. Update the leftmost index to this index and max_row_index to be the current row.
The time complexity is O(m+n) because we can possibly go as far left as we came ahead in the first step.


*/


// The main function that returns index of row with maximum number of 1s.
int rowWithMax1s(bool mat[R][C])
{
    // Initialize first row as row with max 1s
    int max_row_index = 0;
 
    // The function first() returns index of first 1 in row 0.
    // Use this index to initialize the index of leftmost 1 seen so far
    int j = first(mat[0], 0, C-1) - 1;
    if (j == -1) // if 1 is not present in first row
      j = C - 1;
 
    for (int i = 1; i < R; i++)
    {
        // Move left until a 0 is found
        while (j >= 0 && mat[i][j] == 1)
        {
           j = j-1;  // Update the index of leftmost 1 seen so far
           max_row_index = i;  // Update max_row_index
        }
    }
    return max_row_index;
}
