/*

A robot is located at the top-left corner of a m x n grid (marked ‘Start’ in the
diagram below). The robot can only move either down or right at any point in
time. The robot is trying to reach the bottom-right corner of the grid (marked
‘Finish’ in the diagram below). How many possible unique paths are there?

*/

/*
Backtracking Solution:
The most direct way is to write code that traverses each possible path, which can be done using backtracking. When you reach row=m and col=n, you know you’ve reached the bottom-right corner, and there is one additional unique path to it. However, when you reach row>m or col>n, then it’s an invalid path and you should stop traversing. For any grid at row=r and col=c, you have two choices: Traverse to the right or traverse to the bottom. Therefore, the total unique paths at grid (r,c) is equal to the sum of total unique paths from the grid to the right and the grid below. Below is the backtracking code in 5 lines of code:

*/

int backtrack(int r, int c, int m, int n) {
  if (r == m && c == n)
    return 1;
  if (r > m || c > n)
    return 0;
 
  return backtrack(r+1, c, m, n) + backtrack(r, c+1, m, n);
}

/*

Improved Backtracking Solution using Memoization:
Although the above backtracking solution is easy to code, it is very inefficient in the sense that it recalculates the same solution for a grid over and over again. By caching the results, we prevent recalculation and only calculates when necessary. Here, we are using a dynamic programming (DP) technique called memoization.
*/


const int M_MAX = 100;
const int N_MAX = 100;
 
int backtrack(int r, int c, int m, int n, int mat[][N_MAX+2]) {
  if (r == m && c == n)
    return 1;
  if (r > m || c > n)
    return 0;
 
  if (mat[r+1][c] == -1)
    mat[r+1][c] = backtrack(r+1, c, m, n, mat);
  if (mat[r][c+1] == -1)
    mat[r][c+1] = backtrack(r, c+1, m, n, mat);
 
  return mat[r+1][c] + mat[r][c+1];
}
 
int bt(int m, int n) {
  int mat[M_MAX+2][N_MAX+2];
  for (int i = 0; i < M_MAX+2; i++) {
    for (int j = 0; j < N_MAX+2; j++) {
      mat[i][j] = -1;
    }
  }
  return backtrack(1, 1, m, n, mat);
}


/*

Dynamic Programming Solution using Bottom-up Approach: 
If you notice closely,
the above DP solution is using a top-down approach. Now let’s try a bottom-up
approach. Remember this important relationship that is necessary for this DP
solution to work:

The total unique paths at grid (r,c) is equal to the sum of total unique paths
from grid to the right (r,c+1) and the grid below (r+1,c). How can this
relationship help us solve the problem? We observe that all grids of the bottom
edge and right edge must all have only one unique path to the bottom-right
corner. Using this as the base case, we can build our way up to our solution at
grid (1,1) using the relationship above.
*/

const int M_MAX = 100;
const int N_MAX = 100;
 
int dp(int m, int n) {
  int mat[M_MAX+2][N_MAX+2] = {0};
  mat[m][n+1] = 1;
 
  for (int r = m; r >= 1; r--)
    for (int c = n; c >= 1; c--)
      mat[r][c] = mat[r+1][c] + mat[r][c+1];
 
  return mat[1][1];
}
