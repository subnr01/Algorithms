
/* Program to demonstrate bubble sort.
Order of the algorithm is n2


Outer loop selects the element.
Inner loop compares the element with all other positions in the array.
Inner loop selects the position of the element.
When a position is found, the elements are swapped.

*/

void bubble_sort (int *a, int n) {
    int i, t;
    bool swapped = 1;
    while (swapped) {
        swapped = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                swapped = 1;
            }
        }
    }
}

/*
Bubble sort has worst-case and average complexity both О(n2), where
n is the number of items being sorted. There exist many sorting algorithms
with substantially better worst-case or average complexity of O(n log n). 
Even other О(n2) sorting algorithms, such as insertion sort, tend to have better 
performance than bubble sort. 
Therefore, bubble sort is not a practical sorting algorithm when n is large.

The only significant advantage that bubble sort has over
most other implementations, even quicksort, but not insertion sort, 
is that the ability to detect that the list is sorted is efficiently 
built into the algorithm. When the list is already sorted (best-case),
the complexity of bubble sort is only O(n). By contrast, most other algorithms, 
even those with better average-case complexity, perform their entire sorting
process on the set and thus are more complex. However, not only
does insertion sort have this mechanism too, but it also performs better on a 
list that is substantially sorted 
*/
