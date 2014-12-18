/*
Given a Binary Tree, check if all leaves are at same level or not.

          12
        /    \
      5       7       
    /          \ 
   3            1
  Leaves are at same level

          12
        /    \
      5       7       
    /          
   3          
   Leaves are Not at same level


          12
        /    
      5             
    /   \        
   3     9
  /      /
 1      2
 Leaves are at same level

 */


/*

Solution

Need to compare levels of every leaf.
We can set the level of the first leaf
with a new variable and then compare
the level of every subsequent leaf encountered
with the level of this leaf and if we find 
that they are not equal, then definitely
leaves in the tree are not at the same 
level 

*/



/* Recursive function which checks whether all leaves are at same level */
bool checkUtil(struct Node *root, int level, int *leafLevel)
{
    // Base case
    if (root == NULL)  return true;
 
    // If a leaf node is encountered
    if (root->left == NULL && root->right == NULL)
    {
        // When a leaf node is found first time
        if (*leafLevel == 0)
        {
            *leafLevel = level; // Set first found leaf's level
            return true;
        }
 
        // If this is not first leaf node, compare its level with
        // first leaf's level
        return (level == *leafLevel);
    }
 
    // If this node is not leaf, recursively check left and right subtrees
    return checkUtil(root->left, level+1, leafLevel) &&
           checkUtil(root->right, level+1, leafLevel);
}
 
/* The main function to check if all leafs are at same level.
   It mainly uses checkUtil() */
bool check(struct Node *root)
{
   int level = 0, leafLevel = 0;
   return checkUtil(root, level, &leafLevel);
}