/*

Find the intersection of two arrays


For Intersection of two arrays, print the element only if the element is present in both arrays. 
1) Use two index variables i and j, initial values i = 0, j = 0 
2) If arr1[i] is smaller than arr2[j] then increment i. 
3) If arr1[i] is greater than arr2[j] then increment j.
 4) If both are same then print any of them and increment both i and j.
*/

vector<int> findIntersection(vector<int> A, vector<int> B) {
  vector<int> intersection;
  int n1 = A.size();
  int n2 = B.size();
  int i = 0, j = 0;
  while (i < n1 && j < n2) {
    if (A[i] > B[j]) {
      j++;
    } else if (B[j] > A[i]) {
      i++;
    } else {
      intersection.push_back(A[i]);
      i++;
      j++;
    }
  }
  return intersection;
}

