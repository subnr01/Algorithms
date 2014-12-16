
/* 
C program to find largest sum of contigous subarray
using kadane's algorithm

def max_subarray(A):
    max_ending_here = max_so_far = A[0]
    for x in A[1:]:
        max_ending_here = max(x, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far

*/

int maxSubArraySum(int a[], int n)
{
    int sum;

    max_sum = a[0];
    curr_sum = a[0];

    for( int i = 1; i < n ; i++)
    {
        curr_sum = max(a[i], a[i] + curr_sum);
        max_sum = max(curr_sum, max_sum);

    }
    return max_sum;
} 

