/*

Given a matrix (2D array) of m x n elements (m rows, n columns), 
write a function that prints the elements in the array in a spiral manner.

*/

void print_spiral(int mat[][N_MAX], int m, int n, int k) {
  if (m <= 0 || n <= 0)
    return;
  if (m == 1) {
    for (int j = 0; j < n; j++)
      cout << mat[k][k+j] << " ";
    return;
  }
  if (n == 1) {
    for (int i = 0; i < m; i++)
      cout << mat[k+i][k] << " ";
    return;
  }
  // print from top left
  for (int j = 0; j < n - 1; j++)
    cout << mat[k][k+j] << " ";
  // print from top right
  for (int i = 0; i < m - 1; i++)
    cout << mat[k+i][k+n-1] << " ";
  // print from bottom right
  for (int j = 0; j < n - 1; j++)
    cout << mat[k+m-1][k+n-1-j] << " ";
  // print from bottom left
  for (int i = 0; i < m - 1; i++)
    cout << mat[k+m-1-i][k] << " ";
 
  print_spiral(mat, m-2, n-2, k+1);
}
 
void print_spiral_helper(int mat[][N_MAX], int m, int n) {
  print_spiral(mat, m, n, 0);
}