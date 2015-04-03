/*

Given two axis-aligned rectangles A and B. 
Write a function to determine if the two rectangles overlap.


*/

/*

Solution:

Assume that the two rectangles are given as point (P1, P2) and (P3, P4)
respectively. One direct way to attempt this problem is when two rectangles
overlap, one rectangle’s corner point(s) must contain in the other rectangle. Do
keep in mind of the following cases:


As you can see, the conditionals can be pretty complicated as there are a total
eight of them. Can we simplify it further?

A much easier and better approach would be to think from the opposite. How about
asking yourself how the two rectangles cannot overlap each other? Two rectangles
do not overlap when one is above/below, or to the left/right of the other
rectangle.

The condition’s expression is:

! ( P2.y < P3.y || P1.y > P4.y || P2.x < P3.x || P1.x > P4.x )

Using De Morgan’s law, we can further simplify the above expression to:

( P2.y = P3.y && P1.y = P4.y && P2.x = P3.x && P1.x = P4.x )

*/