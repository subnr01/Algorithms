/*

Given an unsorted array and a number n, find if there exists a
 pair of elements in the array whose difference is n.
Examples:
Input: arr[] = {5, 20, 3, 2, 50, 80}, n = 78
Output: Pair Found: (2, 80)

Input: arr[] = {90, 70, 20, 80, 50}, n = 45
Output: No Such Pair

 */

 bool findPair(int arr[], int size, int n)
{
    // Initialize positions of two elements
    int i = 0;  
    int j = 1;
 
    // Search for a pair
    while (i<size && j<size)
    {
        if (i != j && arr[j]-arr[i] == n)
        {
            printf("Pair Found: (%d, %d)", arr[i], arr[j]);
            return true;
        }
        else if (arr[j]-arr[i] < n)
            j++;
        else
            i++;
    }
 
    printf("No such pair");
    return false;
}
