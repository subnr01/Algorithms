/*
Insert element into sorted list 
Given a sorted list with an unsorted number V in the right-most cell, 
can you write some simple code to insert V into the array so it remains sorted?

*/



int insert_sort1( int a[], int size)
{
	for (i = size-2; i <= 0; i--)
	{
		if (a[i] > x)
		{
			a[i+1] = a[i];
		}
		else
		{
			a[i+1] = x;
			break;
		}

	}
}