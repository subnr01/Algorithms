


void printLeaves(struct node* root)
{
    if ( root )
    {
        printLeaves(root->left);
 
        // Print it if it is a leaf node
        if ( !(root->left)  &&  !(root->right) )
            printf("%d ", root->data);
 
        printLeaves(root->right);
    }
}
