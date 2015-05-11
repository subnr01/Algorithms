
/*
Find first missing element in the array 
*/

#include <stdio.h>

int findFirstMissing_2(int array[], int start, int end) {
 
    if(start  > end)
      return end + 1;
 
    if (start != array[start])
      return start;
 
    int mid = (start + end) / 2;
 
    if (array[mid] > mid)
      return findFirstMissing_2(array, start, mid);
    else
      return findFirstMissing_2(array, mid + 1, end);
}

int findFirstMissing( int *a, int low, int high)
{
	int mid;

	if (low >= high) {
		return high + 1;
	}


	if ( a[low] != low)
	{
		return low;
	}

	
	mid = low + (high - low)/2;
		
	if (a[mid] > mid) {
		return findFirstMissing(a, low, mid);
	} else {
		return findFirstMissing(a, mid+1, high);
	}
	

}

int main()
{
	int a[] = {0,1,2,4,5,6,7,8,9};
	//int x = findFirstMissing_2(a, 0, 9);
	int x = findFirstMissing(a, 0, 9);
	
	printf("%d",x);
	return 0;
}
