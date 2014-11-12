

/*
 * Take an ordered binary tree and change it to 
 * circular doubly linked list 
 *
 */


struct tree* treetolist( struct tree *root)
{
    struct tree* start, *end;

    if ( !root)
        return NULL;

    start = treetolist(root->left);
    end = treetolist(root->right);
   
    root->right = root;
    root->left = root;

    start = append(start, root);
    start = append(start, end);

    return start;

}

struct tree* append( struct tree *start, struct tree *end)
{

    if ( !start)
        return end;

    if ( !end)
        return start;

    struct tree *node1 = start->left;
    struct tree *node2 = end->left;  //Note both are pointing to small nodes

    join(node1, end);
    join(node2, start);
 
    return start;  //we are returning the smaller of the two nodes
}

void join( struct tree *node1, struct tree *node2)
{
    node1->right = node2;
    node2->left = node1;
}

