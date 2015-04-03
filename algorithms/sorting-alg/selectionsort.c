/* In selection sort, we get the smallest of the array and put it in
the front of the array, and then with the remaining n-1 elements, find the
smallest and put it in the next position and this continues thus arranging
all the elements in the ascending order.

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
