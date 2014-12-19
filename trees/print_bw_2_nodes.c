/*

Given a binary tree and two level numbers ‘low’ and ‘high’, print nodes from level low to level high.

For example consider the binary tree given in below diagram. 

Input: Root of below tree, low = 2, high = 4

Output:
8 22
4 12
10 14<>


*/



/*

We can print nodes in O(n) time using queue based iterative level
order traversal. The idea is to do simple queue based level order
traversal. While doing inorder traversal, add a marker node at the
end. Whenever we see a marker node, we increase level number. If level
number is between low and high, then print nodes.

*/