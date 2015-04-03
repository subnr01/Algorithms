/*program to demonstrate insertion sort

Worst case performance 	O(n2)
Best case performance 	O(n)
Average case performance 	O(n2)
Worst case space complexity 	O(n) total, O(1) auxiliary
*/


/* Insertion Sort

The outer loop stores the element that needs to be compared.
The inner loop compares the element with its predeccesors.
When a position is found,the current element is put in position in that position in the inner loop.
The element is restored in the outer loop.


*/

#include<stdio.h>

void printarray ( int *a, int n)
{

	int i=0;
	while ( i < n)
	{
		printf ("\t %d ",a[i]);
		i++;
	}
}

void insertionSort(int numbers[], int array_size)
{
  int i, j, index;

  for (i=1; i < array_size; i++)
  {
    index = numbers[i];
    j = i;
    while ((j > 0) && (numbers[j-1] > index))
    {
      numbers[j] = numbers[j-1];
      j = j - 1;
    }
    numbers[j] = index;
  }
}


int main()
{

	int a[8]={5,7,3,8,2,6,4,1};
	printf(" \n Initial  array \n");
	printarray ( a,8);
    insertionSort(a,8);
	printf(" \n Final sorted array \n");
	printarray ( a,8);
}

