/*
 * Write a program that converts a given tree to its Double tree. To create Double tree of the given tree, 
 * create a new duplicate for each node, and insert the duplicate as the left child of the original node. 
 */


void doubleTree(struct node* node) 
{ 
    struct node* oldLeft; 
    if (node==NULL) return; 
    /* do the subtrees */ 
    doubleTree(node->left); 
    doubleTree(node->right); 
    /* duplicate this node to its left */ 
    oldLeft = node->left; 
    node->left = newNode(node->data); 
    node->left->left = oldLeft; 
} 




