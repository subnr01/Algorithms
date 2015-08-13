



bool isBalanced ( struct tree *node)
{
	return maxDepth(node) - minDepth(node) <= 1;
}


int maxDepth(struct tree *node)
{
	if (!node)
		return 0;

	return 1 + max(maxDepth(root->left),maxDepth(root->right));
}


int minDepth(struct tree *node)
{
	if (!node)
		return 0;

	return 1 + min(minDepth(root->left),minDepth(root->right));
}