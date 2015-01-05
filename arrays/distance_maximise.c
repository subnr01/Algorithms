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
