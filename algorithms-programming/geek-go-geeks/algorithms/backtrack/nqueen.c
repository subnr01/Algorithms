/*

Nqueen problem

The N Queen is the problem of placing N chess queens on an 
N×N chessboard so that no two queens attack each other


Desired positions of the eight queens:

 { 0,  1,  0,  0}
 { 0,  0,  0,  1}
 { 1,  0,  0,  0}
 { 0,  0,  1,  0}


*/



bool startcheck ( int board[][], int row, int col, int N)
{
	int i, j;

	//Exit point for the recursive function
	if (col == N) {
		return true;
	}

	for (i = 0; i < N; i++)
	{
		if (isSafe(board, i, col, N))
		{
			board[i][col] = 1;
		}
	
		if (startcheck(board, i, col+1, N))
		{
			return true;
		}

		//backtrack, setting back to false
		board[i][col] = false;
	}
	return false;
}


/* 

Important thing to note is that
we check for clashing queens
only the left side as when come 
into this function, the left side
is set in the caller

*/



bool isSafe ( int board[][], int row, int col, int N)
{

	//Check on the same row
	for (int i = 0; i < col; i++)
	{
		if (board[row][i]) {
			return false;
		}
	}



	//Check on the lower diagonal
	for( i = row, j = col; i < N && j >= 0; i++.j--)
	{
		if (board[i][j]) {
			return false;
		}
	}

	//Check on the upper diagonal
	for( i = row, j = col; i >=0 && j >= 0; i--.j--)
	{
		if (board[i][j]) {
			return false;
		}
	}

	return true;
}







} 