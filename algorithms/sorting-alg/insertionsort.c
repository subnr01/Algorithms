/*program to demonstrate insertion sort

Worst case performance 	O(n2)
Best case performance 	O(n)
Average case performance 	O(n2)
Worst case space complexity 	O(n) total, O(1) auxiliary
*/


/* Insertion Sort

The outer loop stores the element that needs to be compared.
The inner loop compares the element with its predeccesors.
When a position is found,the current element is put in position in that position in the inner loop.
The element is restored in the outer loop.


*/

void insertion_sort (int *a, int n) {
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = a[i];
        for (j = i; j > 0 && t < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = t;
    }
}


/*

Insertion sort many advantages:

1. Simple implementation
2. Stable sort (does not change relative order of elements with equal keys)
3. Adaptive: efficient for already sorted data sets. The time complexity is O(nk) 
   when each element is no more than k places away from its sorted position.
4. In place: Requires O(1) memory
5. Online: Can sort a list as it receives it

When people manually sort something (for example, a deck of playing cards),
most use a method that is similar to insertion sort.

The best case input is an array that is already sorted. 
In this case insertion sort has a linear running time (i.e., O(n)). 
During each iteration, the first remaining element of the input is
only compared with the right-most element of the sorted subsection of the array.

The simplest worst case input is an array sorted in reverse order.
The set of all worst case inputs consists of all arrays where each 
element is the smallest or second-smallest of the elements before it. 
In these cases every iteration of the inner loop will scan and shift the 
entire sorted subsection of the array before inserting the next element. 
This gives insertion sort a quadratic running time (i.e., O(n2)).

The average case is also quadratic, which makes insertion sort impractical 
for sorting large arrays. However, insertion sort is one of the fastest algorithms 
for sorting very small arrays, even faster than quicksort; indeed, good quicksort 
implementations use insertion sort for arrays smaller than a certain threshold, also 
when arising as subproblems; the exact threshold must be determined experimentally and 
depends on the machine, but is commonly around ten.

Insertion sort is very similar to selection sort. 
As in selection sort, after k passes through the array, 
the first k elements are in sorted order. For selection sort 
these are the k smallest elements, while in insertion sort they are 
whatever the first k elements were in the unsorted array. 
Insertion sort's advantage is that it only scans as many elements
as needed to determine the correct location of the k+1st element, 
while selection sort must scan all remaining elements to find the absolute smallest element.

Assuming the k+1st element's rank is random, 
insertion sort will on average require shifting half of 
the previous k elements, while selection sort always requires 
scanning all unplaced elements. So for unsorted input, 
insertion sort will usually perform about half as many comparisons 
as selection sort. If the input array is reverse-sorted, insertion 
sort performs as many comparisons as selection sort. If the input 
array is already sorted, insertion sort performs as few as n-1 comparisons, 
thus making insertion sort more efficient when given sorted or "nearly sorted" arrays.

While insertion sort typically makes fewer comparisons than selection sort, 
it requires more writes because the inner loop can require shifting large sections 
of the sorted portion of the array. In general, insertion sort will write to the array O(n2) 
times, whereas selection sort will write only O(n) times. For this reason selection sort 
may be preferable in cases where writing to memory is significantly more expensive than reading, 
such as with EEPROM or flash memory.

Some divide-and-conquer algorithms such as quicksort and mergesort sort by recursively 
dividing the list into smaller sublists which are then sorted. A useful optimization in 
practice for these algorithms is to use insertion sort for sorting small sublists, where 
insertion sort outperforms these more complex algorithms. The size of list for which insertion 
sort has the advantage varies by environment and implementation, but is typically between eight 
and twenty elements. A variant of this scheme runs quicksort with a constant cutoff K, then runs 
a single insertion sort on the final array:


*/
