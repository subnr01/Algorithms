/*

Given two sorted arrays A, B of size m and n respectively. Find the k-th
smallest element in the union of A and B. You can assume that there are no
duplicate elements.

*/


/*
Solutions

The trivial way, O(m+n): Merge both arrays and the k-th smallest element could
be accessed directly. Merging would require extra space of O(m+n). The linear
run time is pretty good, but could we improve it even further?

A better way, O(k): There is an improvement from the above method, thanks to
readers who suggested this. (See comments below by Martin for an
implementation). Using two pointers, you can traverse both arrays without
actually merging them, thus without the extra space. Both pointers are
initialized to point to head of A and B respectively, and the pointer that has
the larger smaller (thanks to a reader for this correction) of the two is
incremented one step. The k-th smallest is obtained by traversing a total of k
steps. This algorithm is very similar to finding intersection of two sorted
arrays.


The best solution, but non-trivial, O(lg m + lg n): Although the above solution
is an improvement both in run time and space complexity, it only works well for
small values of k, and thus is still in linear run time. Could we improve the
run time further?

The above logarithmic complexity gives us one important hint. Binary search is a
great example of achieving logarithmic complexity by halving its search space in
each iteration. Therefore, to achieve the complexity of O(lg m + lg n), we must
halved the search space of A and B in each iteration.

We try to approach this tricky problem by comparing middle elements of A and B,
which we identify as Ai and Bj. If Ai is between Bj and Bj-1, we have just found
the i+j+1 smallest element. Why? Therefore, if we choose i and j such that i+j =
k-1, we are able to find the k-th smallest element. This is an important
invariant that we must maintain for the correctness of this algorithm.

Summarizing the above,

Maintaining the invariant
i + j = k – 1,

If Bj-1 < Ai < Bj, then Ai must be the k-th smallest,
or else if Ai-1 < Bj < Ai, then Bj must be the k-th smallest.


*/
int findKthSmallest(int A[], int m, int B[], int n, int k) {
  assert(m >= 0); assert(n >= 0); assert(k > 0); assert(k <= m+n);
  
  int i = (int)((double)m / (m+n) * (k-1));
  int j = (k-1) - i;
 
  assert(i >= 0); assert(j >= 0); assert(i <= m); assert(j <= n);
  // invariant: i + j = k-1
  // Note: A[-1] = -INF and A[m] = +INF to maintain invariant
  int Ai_1 = ((i == 0) ? INT_MIN : A[i-1]);
  int Bj_1 = ((j == 0) ? INT_MIN : B[j-1]);
  int Ai   = ((i == m) ? INT_MAX : A[i]);
  int Bj   = ((j == n) ? INT_MAX : B[j]);
 
  if (Bj_1 < Ai && Ai < Bj)
    return Ai;
  else if (Ai_1 < Bj && Bj < Ai)
    return Bj;
 
  assert((Ai > Bj && Ai_1 > Bj) || 
         (Ai < Bj && Ai < Bj_1));
 
  // if none of the cases above, then it is either:
  if (Ai < Bj)
    // exclude Ai and below portion
    // exclude Bj and above portion
    return findKthSmallest(A+i+1, m-i-1, B, j, k-i-1);
  else /* Bj < Ai */
    // exclude Ai and above portion
    // exclude Bj and below portion
    return findKthSmallest(A, i, B+j+1, n-j-1, k-j-1);
}