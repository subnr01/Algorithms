/*

Median of two sorted arrays

*/



class Solution {
public:
      double findMedianSortedArrays(int A[], int m, int B[], int n) {
          int total = m + n;
          if (total & 0x1)
              return find_kth(A, m, B, n, total / 2 + 1);  //IF A AND B TOGETHER HAVE ODD NUMBER OF ELEMENTS
              else
    		 return (find_kth(A, m, B, n, total / 2)
            + find_kth(A, m, B, n, total / 2 + 1)) / 2.0;  //IF A AND B TOGETHER HAVE EVEN NUMBER OF ELEMENTS
      }
      

static int find_kth(int A[], int m, int B[], int n, int k) {
    //always assume that m is equal or smaller than n
    if (m > n) return find_kth(B, n, A, m, k);			
    if (m == 0) return B[k - 1];			//IF THERE ARE NO ELEMENTS IN THE FIRST ARRAY
    if (k == 1) return min(A[0], B[0]);		// IF THERE ARE ONLY TWO ELEMENTS
    //divide k into two parts
    
    int ia = min(k / 2, m), ib = k - ia;	//DIVIDE K INTO TWO PARTS
    
    if (A[ia - 1] < B[ib - 1])
        return find_kth(A + ia, m - ia, B, n, k - ia);  // IF LAST ELEMENT OF A IS LESSER THAN LAST ELEMENT OF B
    else if (A[ia - 1] > B[ib - 1])
        return find_kth(A, m, B + ib, n - ib, k - ib);  // IF LAST ELEMENT OF B IS LESSER THAN LAST ELEMENT OF A
    else
		return A[ia - 1];      //RETURN LAST ELEMENT OF A ( BOTH LAST ELEMENTS ARE EQUAL)
}