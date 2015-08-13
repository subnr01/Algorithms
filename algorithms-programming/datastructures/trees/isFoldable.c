/*
Question: Given a binary tree, find out if the tree can be folded or not.

A tree can be folded if left and right subtrees of the tree are structure wise mirror image of each other. 
An empty tree is considered as foldable.

Consider the below trees:
(a) and (b) can be folded.
(c) and (d) cannot be folded.

(a)
       10
     /    \
    7      15
     \    /
      9  11

(b)
        10
       /  \
      7    15
     /      \
    9       11

(c)
        10
       /  \
      7   15
     /    /
    5   11

(d)

         10
       /   \
      7     15
    /  \    /
   9   10  12

  */
  

 
/* Returns true if the given tree can be folded */
bool IsFoldable(struct node *root)
{
     if (root == NULL)
     {  return true;  }
 
     return IsFoldableUtil(root->left, root->right);
}
 
/* A utility function that checks if trees with roots as n1 and n2
  are mirror of each other */
bool IsFoldableUtil(struct node *n1, struct node *n2)
{
    /* If both left and right subtrees are NULL,
      then return true */
    if (n1 == NULL && n2 == NULL)
    {  return true;  }
 
    /* If one of the trees is NULL and other is not,
      then return false */
    if (n1 == NULL || n2 == NULL)
    {  return false; }
 
    /* Otherwise check if left and right subtrees are mirrors of
       their counterparts */
    return IsFoldableUtil(n1->left, n2->right) &&
           IsFoldableUtil(n1->right, n2->left);
}   