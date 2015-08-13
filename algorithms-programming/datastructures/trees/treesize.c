

int size ( struct tree *node)
{
    if (!node)  
        return 0;

    return (1 + size( node->left) + size( node->right));
}
