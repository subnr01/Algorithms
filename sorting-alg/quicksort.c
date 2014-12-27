/* Program to demonstrate quick sort.


The steps are:

   1. Pick an element, called a pivot, from the list.
   2. Reorder the list so that all elements which are less than the pivot come before the pivot
      and so that all elements greater than the pivot come after it (equal values can go either way). After this
      partitioning, the pivot is in its final position. This is called the partition operation.
   3. Recursively sort the sub-list of lesser elements and the sub-list of greater elements.




In worst Case it makes O(n2)comparisions, on average it makes O(nlogn) comparisions.


*/



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


void qsort(int numbers[], int left, int right)
{
  int pivot, l_hold, r_hold;

  l_hold = left;
  r_hold = right;
  pivot = numbers[left];
  while (left < right)
  {
  printf ("\nfirst\n");
    printarray(numbers,8);
  printf ("\nsecond\n");
     while ((numbers[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      numbers[left] = numbers[right];
      left++;
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      numbers[right] = numbers[left];
      right--;
    }
  printf ("\nfirst\n");
      printarray(numbers,8);
  printf ("\nsecond\n");
  }
  numbers[left] = pivot;
  pivot = left;
  left = l_hold;
  right = r_hold;
  printf ("\n");
  printarray(numbers,8);
  printf ("\n");
  if (left < pivot)
        qsort(numbers, left, pivot-1);
  if (right > pivot)
    qsort(numbers, pivot+1, right);
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