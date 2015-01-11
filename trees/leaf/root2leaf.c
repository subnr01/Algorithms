
void root2leaf(struct tree *node, int path[], int index)
{
	if (!node)
		return;

	if ( !node->left && !node->right)
	{
		print (path, 0, index)
	}

	path[index++] = node->data;
	root2leaf(node->left, path, index)
 	root2leaf(node->right, path, index)
 	
}