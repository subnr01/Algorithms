/* Program to demonstrate quick sort.


The steps are:

   1. Pick an element, called a pivot, from the list.
   2. Reorder the list so that all elements which are less than the pivot come before the pivot
      and so that all elements greater than the pivot come after it (equal values can go either way). After this
      partitioning, the pivot is in its final position. This is called the partition operation.
   3. Recursively sort the sub-list of lesser elements and the sub-list of greater elements.




In worst Case it makes O(n2)comparisions, on average it makes O(nlogn) comparisions.


*/

//http://www.bogotobogo.com/Algorithms/quicksort.php


#include<string.h>
#include<stdio.h>

void printarray( int a[],int size)
{
	int i=0;
	while ( i< size)
	{
		printf( " \t %d ",a[i]);
		i++;
	}
}


/* sort arr[left]...arr[right] into increasing order */
void qsort(int a[], int left_index, int right_index)
{
	int left, right, pivot;
	if(left_index >= right_index) return;

	left = left_index;
	right = right_index;

        // pivot selection
	pivot = a[(left_index + right_index) /2];

        // partition
	while(left <= right) {
		while(a[left] < pivot) left++;
		while(a[right] > pivot) right--;
		if(left <= right) {
			swap(a,left,right);
			left++; right--;
		}
		print(a);		
	}
    
        // recursion
	qsort(a,left_index,right);
	qsort(a,left,right_index);
}

int main()
{
	int a[SIZE]={1, 12, 5, 26, 7, 14, 3, 7, 2};
	print(a);
	qsort(a,0,SIZE-1);
}
void quickSort(int numbers[], int array_size)
{
  qsort(numbers, 0, array_size - 1);
}






int main()
{

	int a[8]={ 1,2,3,4,5,6,7,8};
	quickSort(a, 8);
	printarray(a, 8);
}

/* Quick Sort

Quicksort is a well-known sorting algorithm developed by C. A. R. Hoare that,
on average, makes T(nlogn) (big O notation) comparisons to sort n items. However, in
the worst case, it makes T(n2) comparisons. Typically, quicksort is significantly faster
in practice than other T(nlogn) algorithms, because its inner loop can be efficiently
implemented on most architectures, and in most real-world data, it is possible to make design
choices which minimize the probability of requiring quadratic time.

The steps of the algorithm are:

   1. Pick an element, called a pivot, from the list.
   2. Reorder the list so that all elements which are less than the pivot come
   before the pivot and so that all elements greater than the pivot come after it (equal values
   can go either way). After this partitioning, the pivot is in its final position.
   This is called    the partition operation.
   3. Recursively sort the sub-list of lesser elements and the sub-list of greater elements.


Quicksort is a comparison sort and, in efficient implementations, is not a stable sort.

In the best case, each time we perform a partition we divide the list into two nearly equal pieces.
This means each recursive call processes a list of half the size. Consequently, we can make only logn
nested calls before we reach a list of size 1. This means that the depth of the call tree is T(logn).
But no two calls at the same level of the call tree process the same part of the original list; thus,
each level of calls needs only T(n) time all together (each call has some constant overhead, but since
there are only T(n) calls at each level, this is subsumed in the T(n) factor). The result is that the
algorithm uses only T(nlogn) time.


The most direct competitor of quicksort is heapsort. Heapsort is typically somewhat
slower than quicksort, but the worst-case running time is always T(nlogn).
Quicksort is usually faster, though there remains the chance of worst case performance
except in the introsort variant, which switches to heapsort when a bad case is detected.

Quicksort also competes with mergesort, another recursive sort algorithm but with the
benefit of worst-case T(nlogn) running time. Mergesort is a stable sort, unlike quicksort
and heapsort, and can be easily adapted to operate on linked lists and very large lists stored
on slow-to-access media such as disk storage or network attached storage. Although quicksort can
be written to operate on linked lists, it will often suffer from poor pivot choices without random access.
The main disadvantage of mergesort is that, when operating on arrays, it requires T(n) auxiliary space
in the best case, whereas the variant of quicksort with in-place partitioning and tail recursion uses
only T(logn) space. (Note that when operating on linked lists, mergesort only requires a small, constant
amount of auxiliary storage.)

*/
