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

	 if (!node || elem1 == node->data || elem2 == node->data)
	 	return -1;

	 if( !node->left  && (node->left->data == elem1 || node->left->data == elem2)	)
	 	return node->data


	 if( !node->right  && (node->right->data == elem1 || node->right->data == elem2)	)
	 	return node->data
	 
     
     if ( elem1 > node->data || elem2 < node->data)
     	return node->data

     if ( node->data > elem2 && node->data > elem1) 
     		return LCA(node->left, elem1, elem2)


	if ( node->data < elem2 && node->data < elem1) 
     		return LCA(node->right, elem1, elem2)
    
}	

