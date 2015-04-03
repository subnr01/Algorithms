/*
 *
 * Trim a binary search tree 
 *
 * */

/*
 *
 * http://www.ardendertat.com/2012/01/17/programming-interview-questions-26-trim-binary-search-tree/
 *
 */


/*  
 *  

Given the root of a binary search tree and 2 numbers min and max, trim
the tree such that all the numbers in the new tree are between min and max
(inclusive). The resulting tree should still be a valid binary search tree.
 *   
*/

/*
Using post order traversal
If number is within range then select the node
otherwise discard the node

*/

def trimBST(tree, minVal, maxVal): 
	if not tree: 
		return 

	tree.left=trimBST(tree.left, minVal, maxVal) 
	tree.right=trimBST(tree.right, minVal, maxVal) 

	if minVal <= tree.val <= maxVal: 
		return tree 
	

	if tree.val < minVal: 
		return tree.right 

	if tree.val > maxVal: 
		return tree.left 




