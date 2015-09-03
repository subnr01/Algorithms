
/*
good example of backtacking.

swap the starting element and the ith element
call permutation for the (low + 1) element
swap back the starting and the ith element

*/


/*

First iteration:
ABC --> ABC --> ACB
BAC --> BAC --> BCA
CBA --> CBA --> CAB

*/


void print_permutation( char *s , int low, int high)
{
	if (low == high) {
		printf("%s",a)
		return;
	}


	for ( i = 0; i <= high; i++) 
	{
		swap ( a[low], a[i]);
		print_permutation(a, low + 1, high);
		swap (a[low], a[i]); //backtrack
	}


}