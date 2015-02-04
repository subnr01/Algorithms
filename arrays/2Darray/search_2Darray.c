

/*

Stepwise
1. From the right most position 
    move step by step

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

