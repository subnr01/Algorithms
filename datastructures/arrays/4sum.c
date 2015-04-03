/*
Given an array of integers, find all combination of four elements in the array whose sum is equal to a given value X. O(n^3)
For example, if the given array is {10, 2, 3, 4, 5, 9, 7, 8} and X = 23, then your function should print “3 5 7 8″ (3 + 5 + 7 + 8 = 23).

Following are the detailed steps.
1) Sort the input array.
2) Fix the first element as A[i] where i is from 0 to n–3. After fixing the first element of quadruple, fix the second element as A[j] where j varies from i+1 to n-2. Find remaining two elements in O(n) time, using the method 1 of this post


*/

void find4Numbers(int A[], int n, int X)
{
    int l, r;
 
    // Sort the array in increasing order, using library
    // function for quick sort
    qsort (A, n, sizeof(A[0]), compare);
 
    /* Now fix the first 2 elements one by one and find
       the other two elements */
    for (int i = 0; i < n - 3; i++)
    {
        for (int j = i+1; j < n - 2; j++)
        {
            // Initialize two variables as indexes of the first and last 
            // elements in the remaining elements
            l = j + 1;
            r = n-1;
 
            // To find the remaining two elements, move the index 
            // variables (l & r) toward each other.
            while (l < r)
            {
                if( A[i] + A[j] + A[l] + A[r] == X)
                {
                   printf("%d, %d, %d, %d", A[i], A[j],
                                           A[l], A[r]);
                   l++; r--;
                }
                else if (A[i] + A[j] + A[l] + A[r] < X)
                    l++;
                else // A[i] + A[j] + A[l] + A[r] > X
                    r--;
            } // end of while
        } // end of inner for loop
    } // end of outer for loop
}

