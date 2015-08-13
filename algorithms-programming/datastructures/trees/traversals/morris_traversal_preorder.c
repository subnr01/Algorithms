/*

Morris traversal for 
preorder

*/


/*

1...If left child is null, print the current node data. Move to right
child. ….Else, Make the right child of the inorder predecessor point
to the current node. 
Two cases arise: ………
a) The right child of the
inorder predecessor already points to the current node. Set right
child to NULL. Move to right child of current node. ………
b) The right child is NULL. Set it to current node. Print current node’s 
data and move to left child of current node. 

2...Iterate until current node is not NULL.

*/



// Preorder traversal without recursion and without stack
void morrisTraversalPreorder(struct node* current)
{
    while (current)
    {
        // If left child is null, print the current node data. Move to
        // right child.
        if (current->left == NULL)
        {
            printf( "%d ", current->data );
            current = current->right;
        }
        else
        {
            // Find inorder predecessor
            struct node* pre = current->left;
            while (pre->right && pre->right != current)
                pre = pre->right;
 
            // If the right child of inorder predecessor already points to
            // this node
            if (pre->right == current)
            {
                pre->right = NULL;
                root = current->right;
            }
 
            // If right child doesn't point to this node, then print this
            // node and make right child point to this node
            else
            {
                printf("%d ", current->data);
                pre->right = current;
                current = current->left;
            }
        }
    }
}
