int LCA ( struct tree *node, int elem1, int elem2)
{
	/* LCA is least common ancestor.
	 * basically the element LCA must be greater then left
	 * and lesser than right
	 */

	 /* Cases:
	 1. tree is empty
	 2. One of the children elements is equal to elem1 or elem2.
	 3. Root is greater than both elements
	 4. Root is lesser than both elements. 
	 */

	  if (root == NULL) return NULL;
 
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
 
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
 
    return root;
    
}



/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in BST */
struct node *lca(struct node* root, int n1, int n2)
{
    while (root != NULL)
    {
         // If both n1 and n2 are smaller than root, then LCA lies in left
        if (root->data > n1 && root->data > n2)
           root = root->left;
 
        // If both n1 and n2 are greater than root, then LCA lies in right
        else if (root->data < n1 && root->data < n2)
           root = root->right;
 
        else break;
    }
    return root;
}




