
int binary_search(int *a, int key, int len)
{
	int low = 0;
	int high  = len - 1;
	int mid;

	while ( low <= high)
	{
		mid = low + (high -low)/2;

		if ( a[mid] > key) {
			high = mid - 1;
		}	
		else if (a[mid] < key) {
			low = mid + 1;
		}
		else if (a[mid] == key) {
			return mid;
		}
	}
	return 0;

}

