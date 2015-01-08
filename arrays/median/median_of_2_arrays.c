/*

Find the median of two arrays

*/



double findMedian(int A[], int B[], int l, int r, int nA, int nB) {
if (l > r) return findMedian(B, A, max(0, (nA+nB)/2-nA), min(nB, (nA+nB)/2), nB, nA);
int i = (l+r)/2;
int j = (nA+nB)/2 – i – 1;
if (j ≥ 0 && A[i] < B[j]) return findMedian(A, B, i+1, r, nA, nB);
else if (j < nB-1 && A[i] > B[j+1]) return findMedian(A, B, l, i-1, nA, nB);
else {
if ( (nA+nB)%2 == 1 ) return A[i];
else if (i > 0) return (A[i]+max(B[j], A[i-1]))/2.0;
else return (A[i]+B[j])/2.0;
}
}


/* Another version */

class Solution {
public:
      double findMedianSortedArrays(int A[], int m, int B[], int n) {
          int total = m + n;
          if (total & 0x1)
              return find_kth(A, m, B, n, total / 2 + 1);
          else
    		return (find_kth(A, m, B, n, total / 2)
            			+ find_kth(A, m, B, n, total / 2 + 1)) / 2.0;
      }	

  private:
  	  static int find_kth(int A[], int m, int B[], int n, int k) {
    //always assume that m is equal or smaller than n
    if (m > n) return find_kth(B, n, A, m, k);
    if (m == 0) return B[k - 1];
    if (k == 1) return min(A[0], B[0]);
    //divide k into two parts
    int ia = min(k / 2, m), ib = k - ia;
    if (A[ia - 1] < B[ib - 1])
        return find_kth(A + ia, m - ia, B, n, k - ia);
    else if (A[ia - 1] > B[ib - 1])
        return find_kth(A, m, B + ib, n - ib, k - ib);
    else
return A[ia - 1];
}
};
