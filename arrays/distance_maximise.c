/*
http://leetcode.com/2011/05/a-distance-maximizing-problem.html

Given an array A of integers, find the maximum of j-i 
subjected to the constraint of A[i] < A[j].


*/


/* 

Solutions 1

Brute Force O(N2) 

The straightforward brute force way is to find the shortest
line (the starting index, i), then try to look toward the right side (the ending
index, j) and find a taller line with the furthest distance. Record the distance
(j-i)and repeat with the next shortest line. Clearly, this is an O(N2) algorithm
and we can do better.



Sorting O(N log N)

By sorting the lines according to its height, we can achieve
better run time complexity. Notice that once we sorted the lines, we are able to
find the maximum distance in O(N) time. For each possible original starting
index i, we find the original ending index j, which is the maximum among all j’s
where A[j] > A[i]. To enable the quick search for the maximum, we can build a
look up table in O(N) time by scanning from right to left once. For example, we
start with index i = 4, which is the shortest line. We know the maximum of all
original indices to the right is 7, therefore max distance = 7 – 4 = 3. For the
next line which original index is 3, the max distance = 7 – 3 = 4. Now, we must
skip over the duplicates and reach the line with its original index 1. Here, we
must be careful to skip over all duplicate heights which are not part of the
solution because not satisfying the constraint A[j] > A[i]. Therefore, the max
distance for this case = 2 – 1 = 1.



Best solution O(n) 

Solving this problem efficiently requires some clever
observations to eliminate all unnecessary comparisons. It is non obvious to me
at first if there exists an O(N) algorithm for this problem.

Please look at the above diagram carefully, and ask yourself if you would choose
index a or b as a potential starting point. Clearly, you would never choose
index b as the starting point. Why?

Assume that choosing index b as the starting point, the max distance is j-b,
where A[j] > A[b]. Now, since a < b and A[a] is not taller than A[b] which
implies that A[j] > A[a], we can form a farther distance by choosing a as the
starting index. Therefore, we cannot choose b as the starting point as this
forms a contradiction.

Generally, we want to choose only starting points with no such lines that are
shorter to its left side. From the diagram above, only lines of index 0, 1, 3, 4
are valid starting points.

Once we gather all valid starting points by scanning once from left to right, we
are able to obtain the maximum distance by scanning backwards.

It is obvious that if the ending point is less than the shortest starting point,
then it won’t be a valid solution for all other starting points. Therefore, we
scan from right to left until we meet the first ending point that satisfies the
condition. Then, we proceed to the next shortest starting point, and continue on
from the previous ending point. Using this strategy, we would guarantee that we
are able to find the maximum distance in O(N) running time.

*/



/*
Geeks for Geeks
Examples: 
Input: {34, 8, 10, 3, 2, 80, 30, 33, 1} 
Output: 6 (j = 7, i = 1) 
Input: {9, 2, 3, 4, 5, 6, 7, 8, 18, 0} 
Output: 8 ( j = 8, i = 0) 
Input: {1, 2, 3, 4, 5, 6} 
Output: 5 (j = 5, i = 0) 
Input: {6, 5, 4, 3, 2, 1} 
Output: -1

Solution
To solve this problem, we need to get two optimum indexes of arr[]: left index i and right index j. For an element arr[i], we do not need to consider arr[i] for left index if there is an element smaller than arr[i] on left side of arr[i]. Similarly, if there is a greater element on right side of arr[j] then we do not need to consider this j for right index. So we construct two auxiliary arrays LMin[] and RMax[] such that LMin[i] holds the smallest element on left side of arr[i] including arr[i], and RMax[j] holds the greatest element on right side of arr[j] including arr[j]. After constructing these two auxiliary arrays, we traverse both of these arrays from left to right. While traversing LMin[] and RMa[] if we see that LMin[i] is greater than RMax[j], then we must move ahead in LMin[] (or do i++) because all elements on left of LMin[i] are greater than or equal to LMin[i]. Otherwise we must move ahead in RMax[j] to look for a greater j – i value.
*/


int *LMin = (int *)malloc(sizeof(int)*n); 
int *RMax = (int *)malloc(sizeof(int)*n); 
/* Construct LMin[] such that LMin[i] stores the minimum value 
from (arr[0], arr[1], ... arr[i]) */ 
LMin[0] = arr[0]; 
for (i = 1; i &lt; n; ++i) 
LMin[i] = min(arr[i], LMin[i-1]); 
/* Construct RMax[] such that RMax[j] stores the maximum value 
from (arr[j], arr[j+1], ..arr[n-1]) */ 
RMax[n-1] = arr[n-1]; 
for (j = n-2; j &gt;= 0; --j) 
RMax[j] = max(arr[j], RMax[j+1]); 

i = 0, j = 0, maxDiff = -1; 
while (j <  n && i < n) {
if (LMin[i] < RMax[j]) 
{ 
maxDiff = max(maxDiff, j-i); 
j = j + 1; 
} 
else 
i = i+1; 
} 
return maxDiff; 



/* 
 * Another soluton 


1. Build a tree containing value and index
2. When inserting a right leaf, update its j
3. Compare the index difference of i and j, which can be done in the process of building tree
*/


