/*

Implement queue with 2 stacks

*/

1. Have two stacks s1 and s2.
2. Elements that are added to the queue are pushed to s1 always.
3. When there is a pop operations:
	a. Check top of s2, if not null, pop s2.top
	b. if s2.top == null, then copy s1 elements to s2 and pop s2.top


