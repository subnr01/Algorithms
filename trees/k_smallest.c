/*

Given root of binary search tree and K as input, 
find K-th smallest element in BST.

*/

bool kthsmallest( struct node *root, int *elem, int *k)
{
	if( !root)
		return false;

	if (*k == 0)
	{
		*elem = root->data;
		return true;
	}
	*k -= 1;
	return (kthsmallest(root->left, elem, k) || kthsmallest(root->right, elem, k));

}


