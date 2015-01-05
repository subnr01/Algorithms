/*


Write an efficient algorithm that searches for a value in an n x m table (two-dimensional array). 
This table is sorted along the rows and columns — that is,

Table[i][j] ≤ Table[i][j + 1], 
Table[i][j] ≤ Table[i + 1][j]

*/

/*

Solution

Step-wise Linear Search: We call this the Step-wise Linear Search method.
Similar to Diagonal Binary Search, we begin with the upper right corner (or the
bottom left corner). Instead of traversing diagonally each step, we traverse one
step to the left or bottom. For example, the picture below shows the traversed
path (the red line) when we search for 13.

Essentially, each step we are able to eliminate either a row or a column. The
worst case scenario is where it ended up in the opposite corner of the matrix,
which takes at most 2n steps. Therefore, this algorithm runs in O(n) time, which
is better than previous approaches. 

*/

bool stepWise(int mat[][N_MAX], int N, int target, 
              int &row, int &col) {
  if (target < mat[0][0] || target > mat[N-1][N-1]) return false;
  row = 0;
  col = N-1;
  while (row <= N-1 && col >= 0) {
    if (mat[row][col] < target) 
      row++;
    else if (mat[row][col] > target)
      col--;
    else
      return true;
  }
  return false;
}