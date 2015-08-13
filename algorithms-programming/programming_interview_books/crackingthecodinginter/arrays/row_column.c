#include <stdio.h>
/*
if element of a matrix is 0,
then set the entire row and column
to 0
*/


void setRowColumn(int a[][10], int rows, int columns)
{
	int row[128] = {0};
	int col[128] = {0};

	for ( int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (a[i][j] == 0)
			{
				printf("\n a[i][j] = %d",a[i][j]);
				row[i] = 1;
				col[j] = 1;	
			}
		}
	}
	for (int i = 0; i < rows; i++)
		printf("\n row[i] = %d \n", row[i]);

	for (int i = 0; i < columns; i++)
		printf("\n col[i] = %d \n", col[i]);


	for ( int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if ( row[i] == 1|| col[j] == 1) {
				a[i][j] = 0;
			}
		}
	}
}

int main()
{
	//int a[10][10] = {1,0,1,0,1,1,0,1};
	
	int a[10][10] = {{1,0,1,0} ,{1,1,0,1}};
	setRowColumn(a, 2, 4);
	int i, j;
	for ( int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			printf ("%d ",a[i][j]);
		}
		printf("\n");
	}


}
