/* Demonstrate Merge sort

Merge sort is an O(n log n) comparison based sorting algorithm.
   1. If the list is of length 0 or 1, then it is already sorted. Otherwise:
   2. Divide the unsorted list into two sublists of about half the size.
   3. Sort each sublist recursively by re-applying merge sort.
   4. Merge the two sublists back into one sorted list.

	In sorting n objects, merge sort has an average and worst-case performance of O(n log n).


*/

#include<stdio.h>

void merge(int a[], const int low, const int mid, const int high)
{
  int *temp = new int[high-low+1];
        
  int left = low;
  int right = mid+1;
  int current = 0;
  // Merges the two arrays into temp[] 
  while(left <= mid && right <= high) {
    if(a[left] <= a[right]) {
      temp[current] = a[left];
      left++;
    }
    else { // if right element is smaller that the left
      temp[current] = a[right];  
      right++;
    }
    current++;
  }

  // Completes the array 

        // Extreme example a = 1, 2, 3 || 4, 5, 6
        // The temp array has already been filled with 1, 2, 3, 
        // So, the right side of array a will be used to fill temp.
  if(left > mid) { 
    for(int i=right; i <= high;i++) {
      temp[current] = a[i];
      current++;
    }
  }
        // Extreme example a = 6, 5, 4 || 3, 2, 1
        // The temp array has already been filled with 1, 2, 3
        // So, the left side of array a will be used to fill temp.
  else {  
    for(int i=left; i <= mid; i++) {
      temp[current] = a[i];
      current++;
    }
  }
  // into the original array
  for(int i=0; i<=high-low;i++) {
                a[i+low] = temp[i];
  }
  delete[] temp;
}
 
void merge_sort(int a[], const int low, const int high)
{
  if(low >= high) return;
  int mid = (low+high)/2;
  merge_sort(a, low, mid);  //left half
  merge_sort(a, mid+1, high);  //right half
  merge(a, low, mid, high);  //merge them
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
