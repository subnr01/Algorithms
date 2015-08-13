/*

Given a Binary Tree, print Right view of it. 
Right view of a Binary Tree is set of nodes visible when tree is visited from Right side.

Right view of following tree is 1 3 7 8

          1
       /     \
     2        3
   /   \     /  \
  4     5   6    7
                  \
                   8


 */



// Recursive function to print right view of a binary tree.
void rightViewUtil(struct Node *root, int level, int *max_level)
{
    // Base Case
    if (root==NULL)  return;
 
    // If this is the last Node of its level
    if (*max_level < level)
    {
        printf("%d\t", root->data);
        *max_level = level;
    }
 
    // Recur for right subtree first, then left subtree
    rightViewUtil(root->right, level+1, max_level);
    rightViewUtil(root->left, level+1, max_level);
}
 
// A wrapper over rightViewUtil()
void rightView(struct Node *root)
{
    int max_level = 0;
    rightViewUtil(root, 1, &max_level);
}

