/*

Write a function that takes an arrayA of length n and an index i into A, and rearranges the
elements such that all elements less than A[i] appear first, followed by
elements equal to A[i], followed by elements greater than A[i]. Your algorithm
should have O(1) space complexity and O(n) time complexity.

*/


void dutch_flag_partition(int pivot_index, vector<int>* A) 
{ 
	int pivot = (*A)[pivot_index];
	/**
	* Keep the following invariants during partitioning: * bottom group: (*A)[0 : smaller - 1].
	* middle group: (*A)[smaller : equal - 1].
	* unclassified group: (*A)[equal : larger].
	* top group: (*A)[larger + 1 : A->size() - 1].
	*/
	int smaller = 0, equal = 0, larger = A->size() - 1; // When there is any unclassified element.
	while (equal <= larger) {
	
	if ((*A)[equal] < pivot) { 
		swap((*A)[smaller++], (*A)[equal++]);
	} else if ((*A)[equal] == pivot) { 
			++equal;
		} else { // (*A)[equal] > pivot. 
			swap((*A)[equal], (*A)[larger--]);
		} 
	}
}