/*

Given a set S of n integers, are there elements a, b, c in S such that 
a + b + c = 0? Find all unique triplets in the set which gives the sum of zero.

For example, given set S = {-1 0 1 2 -1 -4},

One possible solution set is:
(-1, 0, 1)
(-1, 2, -1)

Note that (0, 1, -1) is not part of the solution above, because 
(0, 1, -1) is the duplicate of (-1, 0, 1). Same with (-1, -1, 2).

For a set S, there is probably no “the” solution, another solution could be:
(0, 1, -1)
(2, -1, -1)

*/

// returns true if there is triplet with sum equal
// to 'sum' present in A[]. Also, prints the triplet
bool find3Numbers(int A[], int arr_size, int sum)
{
    int l, r;
 
    /* Sort the elements */
    quickSort(A, 0, arr_size-1);
 
    /* Now fix the first element one by one and find the
       other two elements */
    for (int i = 0; i < arr_size - 2; i++)
    {
 
        // To find the other two elements, start two index variables
        // from two corners of the array and move them toward each
        // other
        l = i + 1; // index of the first element in the remaining elements
        r = arr_size-1; // index of the last element
        while (l < r)
        {
            if( A[i] + A[l] + A[r] == sum)
            {
                printf("Triplet is %d, %d, %d", A[i], A[l], A[r]);
                return true;
            }
            else if (A[i] + A[l] + A[r] < sum)
                l++;
            else // A[i] + A[l] + A[r] > sum
                r--;
        }
    }
 
    // If we reach here, then no triplet was found
    return false;
}
