
/*
You are given a list of n-1 integers and these integers are in the range of 1 to n with no duplicates. One of the integers is missing in the list. Write an efficient code to find the missing

Solution 1:
Use the sum formula 


Solution 2:
1) XOR all the array elements, let the result of XOR be X1.
2) XOR all elements from 1 to n. let XOR be X2.
3) XOR of X1 and X2 gives the missing number.

*/


int missing_num(int a[], int sz)
{
	int first = 0;

	for (int i = 0; i < sz; i++)
	{
		first = first ^ a[i];
	}

	for (int i = 0; i <= sz; i++)
	{
		second = second ^ i;
	}
	return first ^ second;
}