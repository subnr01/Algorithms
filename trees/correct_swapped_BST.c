/*
Two of the nodes of a Binary Search Tree (BST) are swapped. Fix (or correct) the BST.

Input Tree:
         10
        /  \
       5    8
      / \
     2   20

In the above tree, nodes 20 and 8 must be swapped to fix the tree.  
Following is the output tree
         10
        /  \
       5    20
      / \
     2   8




*/



/*

Solution

We will maintain three pointers, first, middle and last. When we find the
first point where current node value is smaller than previous node value, we
update the first with the previous node & middle with the current node. When
we find the second point where current node value is smaller than previous
node value, we update the last with the current node. In case #2, we will
never find the second point. So, last pointer will not be updated. After
processing, if the last node value is null, then two swapped nodes of BST are
adjacent.

*/



// This function does inorder traversal to find out the two swapped nodes.
// It sets three pointers, first, middle and last.  If the swapped nodes are
// adjacent to each other, then first and middle contain the resultant nodes
// Else, first and last contain the resultant nodes
void correctBSTUtil( struct node* root, struct node** first,
                     struct node** middle, struct node** last,
                     struct node** prev )
{
    if( root )
    {
        // Recur for the left subtree
        correctBSTUtil( root->left, first, middle, last, prev );
 
        // If this node is smaller than the previous node, it's violating
        // the BST rule.
        if (*prev && root->data < (*prev)->data)
        {
            // If this is first violation, mark these two nodes as
            // 'first' and 'middle'
            if ( !*first )
            {
                *first = *prev;
                *middle = root;
            }
 
            // If this is second violation, mark this node as last
            else
                *last = root;
        }
 
        // Mark this node as previous
        *prev = root;
 
        // Recur for the right subtree
        correctBSTUtil( root->right, first, middle, last, prev );
    }
}

void correctBST( struct node* root )
{
    // Initialize pointers needed for correctBSTUtil()
    struct node *first, *middle, *last, *prev;
    first = middle = last = prev = NULL;
 
    // Set the poiters to find out two nodes
    correctBSTUtil( root, &first, &middle, &last, &prev );
 
    // Fix (or correct) the tree
    if( first && last )
        swap( &(first->data), &(last->data) );
    else if( first && middle ) // Adjacent nodes swapped
        swap( &(first->data), &(middle->data) );
 
    // else nodes have not been swapped, passed tree is really BST.
}
