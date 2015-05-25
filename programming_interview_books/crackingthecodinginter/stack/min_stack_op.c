/* 
Stack with min operation

*/

1. Have two stacks.
2. One for storing the elements and one for storing
   the min in ascending order.


Push operation:
1. If element is lesser than s2.top, then push element to S2.
1. Push element to S1


Pop operation:
1. If s1.top == s2.top then pop from s2.
2. Pop from s1.

Min operation:
1. Return s2.top

