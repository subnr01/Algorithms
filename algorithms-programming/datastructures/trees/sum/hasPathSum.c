/*
 * Given a binary tree and a number, return true if the tree has a root-to-leaf path such that 
 * adding up all the values along the path equals the given number. Return false if no such path can be found.
 */


bool hasPathSum(struct node* node, int sum) 
{ 
/* return true if we run out of tree and sum==0 */ 
if (node == NULL) 
{ 
return(sum == 0); 
} 
else 
{ 
/* otherwise check both subtrees */ 
int subSum = sum - node->data; 
return(hasPathSum(node->left, subSum) || 
hasPathSum(node->right, subSum)); 
} 
} 

