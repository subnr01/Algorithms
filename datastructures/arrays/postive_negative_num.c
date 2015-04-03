/*

An array contains both positive and negative numbers in random order. 
Rearrange the array elements so that positive and negative numbers are 
placed alternatively.

For example, if the input array is [-1, 2, -3, 4, 5, 6, -7, 8, 9], 
then the output should be [9, -7, 8, -3, 5, -1, 2, 4, 6]


*/

void rearrange(int arr[], int n)
{
    // The following few lines are similar to partition process
    // of QuickSort.  The idea is to consider 0 as pivot and
    // divide the array around it.
    int i = -1;
    for (int j = 0; j < n; j++)
    {
        if (arr[j] < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
 
    // Now all positive numbers are at end and negative numbers at
    // the beginning of array. Initialize indexes for starting point
    // of positive and negative numbers to be swapped
    int pos = i+1, neg = 0;
 
    // Increment the negative index by 2 and positive index by 1, i.e.,
    // swap every alternate negative number with next positive number
    while (pos < n && neg < pos && arr[neg] < 0)
    {
        swap(&arr[neg], &arr[pos]);
        pos++;
        neg += 2;
    }
}

