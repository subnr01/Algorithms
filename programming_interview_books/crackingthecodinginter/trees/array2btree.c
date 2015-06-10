/*
Given a sorted array, convert it into a tree with minimal height

*/

struct node* sortedarray2BT( int *a, int low, int high)
{
	if (low < high)
	{
		return NULL;
	}

	int mid = low + (high - low)/2

	struct node *root = getnode(a[mid]);

	root->right =  sortedarray2BT(a, low, mid - 1);
	root->left = sortedarray2BT ( a, mid+1, high);

	return root;
}

