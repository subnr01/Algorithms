
/*

Given a a Binary Tree, find the difference between the sum of nodes at odd level and the sum of nodes at even level. 
Consider root as level 1, left and right children of root as level 2 and so on.

For example, in the following tree, sum of nodes at odd level is (5 + 1 + 4 + 8) which is 18. And sum of nodes at even 
level is (2 + 6 + 3 + 7 + 9) which is 27. The output for following tree should be 18 – 27 which is -9.

      5
    /   \
   2     6
 /  \     \  
1    4     8
    /     / \ 
   3     7   9  


*/

/*

Solution

 Both Children of a node is either at a odd or even place.
 So if we expand recursively, then we find the
 diff of even and odd nodes in the tree

*/


int diff ( struct *node tree)
{

	if (!node)
		return 0;

	return tree->data  - diff(tree->right) - diff(tree->left);
}

