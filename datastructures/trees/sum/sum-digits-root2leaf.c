/*
Given a binary tree, where every node value is a Digit from 1-9 .Find the sum of all the numbers which are formed
from root to leaf paths.

For example consider the following Binary Tree.

                                          6
                                      /      \
                                    3          5
                                  /   \          \
                                 2     5          4  
                                      /   \
                                     7     4
  There are 4 leaves, hence 4 root to leaf paths:
   Path                    Number
  6->3->2                   632
  6->3->5->7               6357
  6->3->5->4               6354
  6->5>4                    654   
Answer = 632 + 6357 + 6354 + 654 = 13997 

*/



/* 

Solution

Solution is simple. 
Take the root and mulitply by 10 and add
the child element. Keep doing
this until u reach a leaf.
Run recursively until u get the final sum.

*/


// Returns sum of all root to leaf paths. The first parameter is root
// of current subtree, the second parameter is value of the number formed
// by nodes from root to this node
int treePathsSumUtil(struct node *root, int val)
{
    // Base case
    if (root == NULL)  return 0;
 
    // Update val
    val = (val*10 + root->data);
 
    // if current node is leaf, return the current value of val
    if (root->left==NULL && root->right==NULL)
       return val;
 
    // recur sum of values for left and right subtree
    return treePathsSumUtil(root->left, val) +
           treePathsSumUtil(root->right, val);
}
