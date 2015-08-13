

int binary_search_recur ( int *a, int key, int low, int high)
{
	if ( low > high) {
			return -1;
	}

	int mid = low + (high - low)/2;

	if ( a[mid] == key) {
		return mid;
	}

	else if ( a[mid] < key) {
		return binary_search_recur(a, key, mid+1, high);
	}
	else if ( a[mid] > key) {
		return binary_search_recur(a, key, low, mid-1);
	}
}