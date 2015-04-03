
int minTree(struct tree *node)
{
	if (!node)
		return -1;

	if (!node->left)
		return node->data;

	return minTree(node->left);	 
}
