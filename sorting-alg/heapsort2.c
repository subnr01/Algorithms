#include<stdio.h>
//#include<conio.h>
#include<math.h>


void swap(int *p, int *q);
void HEAPSORT(int heap[100], int n);
int BUILD_HEAP(int heap[100],int n);
void HEAPIFY(int heap[100], int i, int heap_size);

int PARENT(int i);
int LEFT(int i);
int RIGHT(int i);

//int heap_size;

void main()
{
int i,j,n;
int heap[110];

while(1)
	{
	printf("Enter the number of element (0 to exit): ");
	scanf("%d",&n);
	if(n==0)
		break;
	for(i=1;i<=n;++i)
		scanf("%d",&heap[i]);
	HEAPSORT(heap,n);
	printf("The sorted List is:\n");
	for(i=1;i<=n;++i)
		printf("%d ",heap[i]);
	}
}

void HEAPSORT(int heap[100], int n)
{
int i,heap_size,j;
heap_size = BUILD_HEAP(heap,n);
printf ("\n");

for(i=n;i>=2;--i)
	{

	for(j=1;j<=n;++j)
				printf(" \t %d ",heap[j]);

	printf ("\n");

	swap(&heap[1],&heap[i]);
	--heap_size;
		for(j=1;j<=n;++j)
				printf(" \t %d ",heap[j]);

	HEAPIFY(heap,1,heap_size);
		printf ("\n");
	}

}

void swap(int *p, int *q)
{
int t;
t=*p;
*p=*q;
*q=t;
}

int BUILD_HEAP(int heap[100],int n)
{
int i, heap_size;
heap_size = n;
for(i=floor(n/2);i>=1;--i)
	HEAPIFY(heap,i,heap_size);
return heap_size;
}

void HEAPIFY(int heap[100], int i, int heap_size)
{
int l,r,largest;
l = LEFT(i);
r = RIGHT(i);

if(l <= heap_size && heap[l] > heap[i])
	largest = l;
else
	largest = i;
if(r <= heap_size && heap[r] > heap[largest])
	largest = r;
if(largest != i)
	{
	swap(&heap[i],&heap[largest]);
	HEAPIFY(heap,largest,heap_size);
	}

}

int PARENT(int i)
	{return (i/2);}
int LEFT(int i)
	{return (2*i);}
int RIGHT(int i)
	{return ((2*i)+1);}

