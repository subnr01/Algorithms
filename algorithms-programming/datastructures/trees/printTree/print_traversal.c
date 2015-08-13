

void postorder_traversal( struct tree * node)
{
    if (!node) {
        return;
    }else {
        postorder_traversal (node->left);
        postorder_traversal (node->right);
        print (node->data);
    }
}

void preorder( struct node *tree)
{
    if (!node) {
        return;
    }else {
        print(node->data);
        preoder(node->left);
        preorder(node->right);
    }
}
