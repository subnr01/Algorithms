#include <stdio.h>
/*
Rotate a 2D array by 90
*/


/*
1) original matrix

1 2 3
4 5 6
7 8 9

2) transpose

1 4 7
2 5 8
3 6 9

3-a) change rows to rotate left

3 6 9
2 5 8
1 4 7

3-b) or change columns to rotate right

7 4 1
8 5 2
9 6 3

*/

void printmatrix( int a[][10])
{
	for ( int i = 0 ; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			printf (" %d",a[i][j]);
		}
		printf("\n");
	}
}


void rotate(int matrix[][10], int n) 
{ 
	printmatrix(matrix);
	printf("\n");
	for (int layer = 0; layer < n / 2; ++layer) {
		int first = layer; 
		int last = n-1-layer;
		for(int i = first; i < last; ++i) {

			int offset = i - first;
			int top = matrix[first][i]; // save top
			
			printf ("\n i = %d, offset is %d and top is %d\n",i, offset,top);
			// left -> top
			matrix[first][i] = matrix[last-offset][first];
			
			// bottom -> left
			matrix[last-offset][first] = matrix[last][last - offset];
			
			// right -> bottom
			matrix[last][last - offset] = matrix[i][last];
			
			// top -> right
			matrix[i][last] = top; // right <- saved top 
			printmatrix(matrix);	
			printf("\n done\n");
		}
		printf ("\n second \n");
		
	 }
}

int main()
{
	int a[10][10] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	rotate(a,4);
	printf("\n result \n");
	printmatrix(a);
}






