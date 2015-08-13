#include<stdio.h>
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
int i,heap_size;
heap_size = BUILD_HEAP(heap,n);
for(i=n;i>=2;--i)
	{
	swap(&heap[1],&heap[i]);
	--heap_size;
	HEAPIFY(heap,1,heap_size);
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


/* Heap sort

Heapsort (method) is a comparison-based sorting algorithm,
and is part of the selection sort family. Although somewhat
slower in practice on most machines than a good implementation
of quicksort, it has the advantage of a worst-case T(n log n) runtime.

The heap sort works as its name suggests. It begins by building a
heap out of the data set, and then removing the largest item and placing
it at the end of the sorted array. After removing the largest item, it
reconstructs the heap and removes the largest remaining item and plac
es it in the next open position from the end of the sorted array.
This is repeated until there are no items left in the heap and the
sorted array is full.

Heapsort inserts the input list elements into a heap data structure.
The largest value (in a max-heap) or the smallest value (in a min-heap)
are extracted until none remain, the values having been extracted in sorted
order. The heap's invariant is preserved after each extraction, so the only
cost is that of extraction.

Comparision with other sorts
Heapsort primarily competes with quicksort, another very efficient
general purpose nearly-in-place comparison-based sort algorithm.

Quicksort is typically somewhat faster, due to better cache behavior and
other factors, but the worst-case running time for quicksort is O(n2), which is
unacceptable for large data sets and can be deliberately triggered given enough
knowledge of the implementation, creating a security risk. See quicksort for a
detailed discussion of this problem, and possible solutions.

Thus, because of the O(n log n) upper bound on heapsort's running time and constant
upper bound on its auxiliary storage, embedded systems with real-time constraints or
systems concerned with security often use heapsort.

Heapsort also competes with merge sort, which has the same time bounds, but requires
O(n) auxiliary space, whereas heapsort requires only a constant amount. Heapsort also
typically runs more quickly in practice on machines with small or slow data caches. On
the other hand, merge sort has several advantages over heapsort:

    * Like quicksort, merge sort on arrays has considerably better data cache performance,
    often outperforming heapsort on a modern desktop PC, because it accesses the elements in order.
    * Merge sort is a stable sort.
    * Merge sort parallelizes better; the most trivial way of parallelizing merge sort
    achieves close to linear speedup, while there is no obvious way to parallelize heapsort at all.
    * Merge sort can be easily adapted to operate on linked lists and very large lists
    stored on slow-to-access media such as disk storage or network attached storage.
    Heapsort relies strongly on random access, and its poor locality of reference makes
    it very slow on media with long access times.
*/
An interesting alternative to Heapsort is Introsort which combines quicksort and heapsort
to retain advantages of both: worst case speed of heapsort and average speed of quicksort.