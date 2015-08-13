/*
Seidwick:
1. Find the smallest element in the array and exchange it with the first element.
2. Find the next smallest element in the array and exchange it with the seond element.
3. Repeated selection of the smallest element and exchange operations result in a sorted array.
However in the impementation it works differently as we consider 
the first element to be the smallest and swap to any element smaller 
than the first element as we move along the array. At the end of the array 
pass, we end up with the index of the least element. 
We swap this least element with the first element.
Then we consider the second element as the smallest and
do the same operation.
We do this until we reach the end of the array.

Optimisation:
The outer loop moves till n-2. If we reached till n-2, then 
for all practical purposes we found elements less 
than n-1 to the left of n-1. So we can leave out the
last iteration.

We can avoid swapping an element with its own index
if we found that the element chosen is indeed the
smallest in the array. This can be quite useful 
when we operate on already partially sorted arrays.

The swapping is outside the inner loop, so there can be atmost N swaps.
The compares run in the loop and so the running time is dominated by the 
number of compares.
Selection sort uses (n^2)/2 compares and N exchanges to sort of array of length N.
It is inefficient for large arrays.

Selection sort is noted for its simplicity, and it has performance advantages 
over more complicated algorithms in certain situations, particularly 
where auxiliary memory is limited.


Properties:
1. It is an inplace comparision sort.
2. Running time is insensistive to input. So it takes about as long to run selection sort
   for an array that is already in order. There are other algorithms that can take
   advantage of initial order in the input.
3. Data movement is minimal:  Number of array accesses is linear function of the array size
   as the sorting algorithm uses N exchanges.
4.  Its primary purpose is for when writing data is very expensive (slow) 
    when compared to reading, eg. writing to flash memory or EEPROM. 
    No other sorting algorithm has less data movement.


Comparison with other Sorting algorithms:
1. Selection Sort outperforms Bubble sort in the average case.
2. While selection sort is preferable to insertion sort in terms of 
   number of writes (Θ(n) swaps versus Ο(n2) swaps), it almost always 
   far exceeds (and never beats) the number of writes that cycle sort makes, 
   as cycle sort is theoretically optimal in the number of writes. This can be 
   important if writes are significantly more expensive than reads, such as with 
   EEPROM or Flash memory, where every write lessens the lifespan of the memory.
3. insertion sort will  usually perform about half as many comparisons as 
   selection sort, although it can perform just as many or far fewer depending on the 
   order the array was in prior to sorting.
4. Selection sort is greatly outperformed on larger arrays by Θ(n log n) 
   divide-and-conquer algorithms such as mergesort. However, insertion sort 
   or selection sort are both typically faster for small arrays (i.e. fewer 
   than 10–20 elements). A useful optimization in practice for the recursive algorithms
   is to switch to insertion sort or selection sort for "small enough" sublists.
*/




void selectionsort (  T a[], int n)
{
	int i,j,least;
	for ( i =0;i<n-1;i++)
	{
		least=i;
		for ( j=i+1; j<n;j++)
		{
			if ( a[j] <a[least])
				least=j;
		}
		if ( i!=least)
		swap ( a[least],a[i]);
	}
}
