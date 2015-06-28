/*program to demonstrate insertion sort

Worst case performance 	O(n2)
Best case performance 	O(n)
Average case performance 	O(n2)
Worst case space complexity 	O(n) total, O(1) auxiliary
*/

/*
Siedwick:
As in selection sort, the items to the left of the current index are in sorted order
during the sort, but they are not in their final position, as they may have to be moved 
to make room for smaller items encountered later. The array is, however, fully sorted 
when the index reaches the right end.
Unlike that of selection sort, the running time of insertion sort depends on the 
ini- tial order of the items in the input. For example, if the array is 
large and its entries are already in order (or nearly in order), then insertion
sort is much, much faster than if the entries are randomly ordered or in reverse order.


Insertionsort uses (n^2)/4 compares and (n^2)/4 exchanges to sort a randomly ordered
array of length N with distinct keys on the average.
The worst cast is (n^2)/2 compares and (n^2)/2 exchanges and the best case is 
(n-1) compares and 0 exchanges.

Insertion sort works well for certain types of nonrandom arrays that often arise
in practice, even if they are huge. For example, as just mentioned, consider what 
happens when you use insertion sort on an array that is already sorted. 
Each item is immediately determined to be in its proper place in the array, 
and the total running time is linear.

More generally, we consider the concept of a partially sorted array, 
as follows: An inversion is a pair of entries that are out of order
in the array.
If the number of inversions in an array are less a constant multiple
of the array size, we say that the array is partially sorted.
Typical examples of partially sorted arrays are the following:
■ An array where each entry is not far from its final position
■ A small array appended to a large sorted array
■ An array with only a few entries that are not in place
Insertion sort is an efficient method for such arrays; selection sort is not. 
Indeed, when the number of inversions is low, insertion sort is likely to 
be faster than any sorting method 

The number of exchanges used by insertion sort is equal to the
number of inversions in the array and the number of compares
is at least equal to the number of inversions plus 
the array size - 1.

It is not difficult to speed up insertion sort substantially, by shortening its inner loop to
move the larger entries to the right one position rather than doing full exchanges

In summary, insertion sort is an excellent method for partially sorted arrays and is also a 
fine method for tiny arrays. These facts are important not just because such arrays frequently 
arise in practice, but also because both types of arrays arise in intermediate stages of
advanced sorting algorithms, so we will be considering insertion sort again in relation to such algorithms.

The running times of insertion sort and selection sort are quadratic 
and within a small constant factor of one another for randomly ordered arrays of distinct values.

Insertion sort is slow for large un- ordered arrays because the only exchanges 
it does involve adjacent entries, so items can move through the array only one 
place at a time. For example, if the item with the 
smallest key happens to be at the end of the array, 
n-1 exchanges are needed to get that one item where it belongs.

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



