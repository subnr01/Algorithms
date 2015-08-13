Given a stream of unsorted integers, find the median element in sorted order at any given time.

So, we will be receiving a continuous stream of numbers in some random order and we don’t know the stream length in advance. Write a function that finds the median of the already received numbers efficiently at any time. We will be asked to find the median multiple times. Just to recall, median is the middle element in an odd length sorted array, and in the even case it’s the average of the middle elements.

Following approaches:
1.  We could insert the  integers to an unsorted array.  Inserting will take O(1) time  while  finding the median will take O(N) time using the Median of Medians algorithm. Since the algorithm does not find the median efficiently, it cannot be considered.
2.  We could use a sorted array. Finding the position where we want to insert will take us 
O (logN) time, but after finding the postion, we have to shift the elements to the right. This will take O(N) complexity.  So inserting will take O(logN ) time , the overall insertion complexity is O(N) due to shifting. we can just return the middle element if the array length is odd, or the average of middle elements if the length is even. This can be done in O(1) time, which is exactly what we’re looking for. But finding the median is still extremely efficient, constant time. However, linear time insertion is pretty inefficient and we would prefer a better performance.
3.  If we use unsorted linked list, then we can insert into either as head or tail which is O(N) but we suffer the same problem of unsorted array where finding the median is O(N).  
4.  Insertion into a sorted linked list is O(N) because we cannot perform binary search in a linked list even if it is sorted. So, using a sorted linked list doesn’t worth the effort, insertion is O(N) and finding median is O(1), same as the sorted array.
5.  If we use a binary tree with additional information such as number of nodes in the tree, then we can find the median in O(logN) time, taking the appropriate branch in the tree based on number of children on the left and right of the current node. However, the insertion complexity is O(N) because a standard binary search tree can degenerate into a linked list if we happen to receive the numbers in sorted order.
6.  Balanced binary search trees seem to be the most optimal solution, insertion is O(logN) and find median is O(1).

Solution

We will use a max heap and a min heap with 2 requirements. 
1.  The first requirement is that the max heap contains the smallest half of the numbers and min heap contains the largest half. So, the numbers in max-heap are always less than or equal to the numbers in min-heap.
2.  The second requirement is that the number of elements in max-heap is either equal or 1 more than the number of elements in the min heap. So, if we received 2N elements (even) up to now, max-heap and min-heap will both contain N elements. Otherwise, if we have received 2N+1 elements (odd), max-heap will contain N+1 and min-heap N. 

The heaps are constructed considering the two requirements above. Then once we’re asked for the median, if the total number of received elements is odd, the median is the root of the max-heap. If it’s even, then the median is the average of the roots of the max-heap and min-heap.


1.  When the number of elements in even, then the element is inserted into the max heap. If the new element is less than all the elements in the min heap, then we are done. If the new element is greater than the root of the min heap, then this element will be the root of the max heap as well. Now to follow the first requirement, we need to swap the roots of max heap and min heap such that the bottom half belongs to max heap and the top half belongs to min heap.
2.  If the number of elements in odd, then the new element is inserted into the max heap. We then pop the root element from the max heap and push it to the min heap so the first requirement is met.

Insertion complexity is O(logN) and finding the median is O(1).
class streamMedian:
    def __init__(self):
        self.minHeap, self.maxHeap = [], []
        self.N=0
 
    def insert(self, num):
        if self.N%2==0:
            heapq.heappush(self.maxHeap, -1*num)
            self.N+=1
            if len(self.minHeap)==0:
                return
            if -1*self.maxHeap[0]>self.minHeap[0]:
                toMin=-1*heapq.heappop(self.maxHeap)
                toMax=heapq.heappop(self.minHeap)
                heapq.heappush(self.maxHeap, -1*toMax)
                heapq.heappush(self.minHeap, toMin)
        else:
            toMin=-1*heapq.heappushpop(self.maxHeap, -1*num)
            heapq.heappush(self.minHeap, toMin)
            self.N+=1
 
    def getMedian(self):
        if self.N%2==0:
            return (-1*self.maxHeap[0]+self.minHeap[0])/2.0
        else:
            return -1*self.maxHeap[0]


