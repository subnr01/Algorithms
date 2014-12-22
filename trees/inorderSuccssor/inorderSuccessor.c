/*

In Binary Tree, Inorder successor of a node is the next node in Inorder
traversal of the Binary Tree. Inorder Successor is NULL for the last node in
Inoorder traversal. In Binary Search Tree, Inorder Successor of an input node
can also be defined as the node with the smallest key greater than the key of
input node. So, it is sometimes important to find next node in sorted order.

*/




struct node * inOrderSuccessor(struct node *root, struct node *n)
{
    // step 1 of the above algorithm
    if( n->right != NULL )
        return minValue(n->right);
 
    struct node *succ = NULL;
 
    // Start from root and search for successor down the tree
    while (root != NULL)
    {
        if (n->data < root->data)
        {
            succ = root;
            root = root->left;
        }
        else if (n->data > root->data)
            root = root->right;
        else
           break;
    }
 
    return succ;
}