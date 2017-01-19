
void root2leaf(struct tree *node, int path[], int index)
{
	if (!node)
		return;

	
	path[index++] = node->data;
	if ( !node->left && !node->right)
	{
		print (path, 0, index)
	}

	
	root2leaf(node->left, path, index)
 	root2leaf(node->right, path, index)
 	
}

/* What about storing all paths ????? */
