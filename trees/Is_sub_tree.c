/*

Given two binary trees, check if the first tree is subtree of the second one. A subtree of a tree T is a tree S consisting of a node in T and all of its descendants in T. The subtree corresponding to the root node is the entire tree; the subtree corresponding to any other node is called a proper subtree.

For example, in the following case, tree S is a subtree of tree T.

        Tree S
          10  
        /    \ 
      4       6
       \
        30


        Tree T
              26
            /   \
          10     3
        /    \     \
      4       6      3
       \
        30

  */

/* This function returns true if S is a subtree of T, otherwise false */
bool isSubtree(struct node *T, struct node *S)
{
    /* base cases */
    if (S == NULL)
        return true;
 
    if (T == NULL)
        return false;
 
    /* Check the tree with root as current node */
    if (areIdentical(T, S))
        return true;
 
    /* If the tree with root as current node doesn't match then
       try left and right subtrees one by one */
    return isSubtree(T->left, S) ||
           isSubtree(T->right, S);
}




