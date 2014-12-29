/*



Given an array of positive integers. All numbers occur even number of times
except one number which occurs odd number of times. Find the number in O(n) time
& constant space.

*/


/* 
Solution: 
Do a bit wise XOR of all the elements. The elements that appear
even number of times will end up becoming zero leaving the odd element. The
element left out is the one that appears odd number of times.

*/


int ret( int a[], int sz)
{
	int res;
	for (int i = 0; i < sz; i++)
	{
		res = res ^ a[i];
	}
	return res;
}