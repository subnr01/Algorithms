Given an array of n elements, where each element is at most k away from its
target position, devise an algorithm that sorts in O(n log k) time.  For
example, let us consider k is 2, an element at index 7 in the sorted array, can
be at indexes 5, 6, 7, 8, 9 in the given array. 

1) Create a Min Heap of size k+1
with first k+1 elements. This will take O(k) time (See this GFact) 
2) One by one remove min element from heap, put it in result array, 
and add a new element to heap from remaining elements.
3 )Removing an element and adding a new element to 
min heap will take Logk time. So overall complexity will be O(k) + O((n-k)*logK)
