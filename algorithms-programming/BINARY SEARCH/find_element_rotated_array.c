
/*

Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2). How do you find an element in
the rotated array efficiently? You may assume no duplicate exists in the array.


*/


int rotated_binary_search(int A[], int N, int key) {
  int L = 0;
  int R = N - 1;
 
  while (L <= R) {
    // Avoid overflow, same as M=(L+R)/2
    int M = L + ((R - L) / 2);
    if (A[M] == key) return M;
 
    // the bottom half is sorted
    if (A[L] <= A[M]) {
      if (A[L] <= key && key < A[M])
        R = M - 1;
      else
        L = M + 1;
    }
    // the upper half is sorted
    else {
      if (A[M] < key && key <= A[R])
        L = M + 1;
      else 
        R = M - 1;
    }
  }
  return -1;
}