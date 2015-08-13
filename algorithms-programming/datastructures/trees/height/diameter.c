/*

Find diameter of a tree

*/

/*

The diameter of a tree (sometimes called the width) is the number 
of nodes on the longest path between two leaves in the tree. 

The diameter of a tree T is the largest of the following quantities:

* the diameter of T’s left subtree
* the diameter of T’s right subtree
* the longest path between leaves that 
goes through the root of T (this can be computed 
from the heights of the subtrees of T)

*/


/* Function to get diameter of a binary tree */
int diameter(struct node * tree)
{
   /* base case where tree is empty */
   if (tree == 0)
     return 0;
 
  /* get the height of left and right sub-trees */
  int lheight = height(tree->left);
  int rheight = height(tree->right);
 
  /* get the diameter of left and right sub-trees */
  int ldiameter = diameter(tree->left);
  int rdiameter = diameter(tree->right);
 
  /* Return max of following three
   1) Diameter of left subtree
   2) Diameter of right subtree
   3) Height of left subtree + height of right subtree + 1 */
  return max(lheight + rheight + 1, max(ldiameter, rdiameter));
} 

