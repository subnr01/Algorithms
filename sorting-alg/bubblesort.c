
/* Program to demonstrate bubble sort.
Order of the algorithm is n2


Outer loop selects the element.
Inner loop compares the element with all other positions in the array.
Inner loop selects the position of the element.
When a position is found, the elements are swapped.



*/

#include <stdio.h>
#define MAX 10
/* Swapping two variables*/

void swap(int *x,int *y)
{
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

/* The inner loop compares elements sequentially and swaps them if it finds that the greater element is
   at a lower index*/

void bsort(int list[], int n)
{
   int i,j;
   for(i=0;i<(n);i++)			/* outer loop*/
   {
      for(j=0;j<(n);j++)
      {
      	if(list[j] > list[j+1])
                    swap(&list[j],&list[j+1]);
      }
}
}


void readlist(int list[],int n)
{
   int i;
   printf("Enter the elements\n");
   for(i=0;i<n;i++)
       scanf("%d",&list[i]);
}




void printlist(int list[],int n)
{
   int i;
   printf("The elements of the list are: \n");
   for(i=0;i<n;i++)
      printf("%d\t",list[i]);
}


void main()
{

   int list[MAX];
   int n;
   printf("Enter the number of elements in the list max = 10\n");
   scanf("%d",&n);
   readlist(list,n);
   printf("The list before sorting is:\n");
   printlist(list,n);
   bsort(list,n);
   printf("The list after sorting is:\n");
   printlist(list,n);
}

