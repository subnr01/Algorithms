/* Demonstrate Merge sort

Merge sort is an O(n log n) comparison based sorting algorithm.
   1. If the list is of length 0 or 1, then it is already sorted. Otherwise:
   2. Divide the unsorted list into two sublists of about half the size.
   3. Sort each sublist recursively by re-applying merge sort.
   4. Merge the two sublists back into one sorted list.

	In sorting n objects, merge sort has an average and worst-case performance of O(n log n).


*/

#include<stdio.h>

void move (int *list1, int first1, int last1, int *list2, int first2) {
  while (first1 <= last1)
    list2[first2++] = list1[first1++];
}


void printarray ( int *a, int n)
{

	int i=0;
	printf ( "\n");
	while ( i < n)
	{
		printf ("\t %d ",a[i]);
		i++;
	}
	printf ( "\n");
}



void merge (int *A, int first1, int last1, int first2, int last2) {
  int temp[8];
  int index, index1, index2;
  int num;

  index = 0;
  index1 = first1;
  index2 = first2;

  printf (" \n a[first1]=%d, first1=%d  first2=%d",A[first1],first1,first2);
  printf (" \n a[second2]=%d, last1=%d   last2=%d\n",A[last2],last1,last2);
  num = last1 - first1 + last2 - first2 + 2;

  /*
   *  Merge the two lists back together until one list runs out of
   *  items...
   *
   */

  while ((index1 <= last1) && (index2 <= last2)) {
    if (A[index1] < A[index2]) temp[index++] = A[index1++];
    else temp[index++] = A[index2++];
  }

  /*
   *  At which point fill in the merged list with the "rest" of the
   *  non exhausted list.
   *
   */

  if (index1 > last1)
    move (A, index2, last2, temp, index);
  else
    move (A, index1, last1, temp, index);


  /* finally move our merged array in temp space to the real array */
  move(temp, 0, num-1, A, first1);
  printf (" \n A[0]=%d, A[num-1]=%d \n",A[0],A[num-1]);
}



void merge_sort (int *array, int left, int right) {

  printf ("\n %d , %d \n",array[left], array[right]);
  if (left < right) {
    merge_sort (array, left, (left+right)/2);
    merge_sort (array, (left+right)/2 + 1, right);
    merge (array, left, (left+right)/2, (left+right)/2+1, right);
  	printf ( "\n after merge \n");
  	printarray ( array,8);
  	printf ( "\n after merge \n");
  }
}


int main()
{

	int a[8]={3,8,5,9,2,7,6,1};
	printf(" \n Initial  array \n");
	printarray ( a,8);
	merge_sort (a,0,7);
	printf(" \n Final sorted array \n");
	printarray ( a,8);
}



/*

Merge sort is an O(n log n) comparison-based sorting algorithm.
In most implementations it is stable, meaning that it preserves
the input order of equal elements in the sorted output.
Conceptually, a merge sort works as follows:

   1. If the list is of length 0 or 1, then it is already sorted. Otherwise:
   2. Divide the unsorted list into two sublists of about half the size.
   3. Sort each sublist recursively by re-applying merge sort.
   4. Merge the two sublists back into one sorted list.

Merge sort incorporates two main ideas to improve its runtime:

   1. A small list will take fewer steps to sort than a large list.
   2. Fewer steps are required to construct a sorted list from two sorted lists than
   two unsorted lists. For example, you only have to traverse each list once if they're
   already sorted (see the merge function below for an example implementation).

In sorting n objects, merge sort has an average and worst-case performance of O(n log n).
Although heapsort has the same time bounds as merge sort,
it requires only T(1) auxiliary space instead of merge sort's T(n),
and is often faster in practical implementations. Quicksort, however,
is considered by many[who?] to be the fastest general-purpose sort algorithm.
On the plus side, merge sort is a stable sort, parallelizes better, and is
more efficient at handling slow-to-access sequential media. Merge sort is
often the best choice for sorting a linked list: in this situation it is
relatively easy to implement a merge sort in such a way that it requires only
T(1) extra space, and the slow random-access performance of a linked list makes
some other algorithms (such as quicksort) perform poorly, and others (such as heapsort)
completely impossible.



*/