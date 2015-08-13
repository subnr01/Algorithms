void tree mirrorTree( struct tree *node)
{
	if ( !node)
		return;

	mirrorTree(node->left)
	mirrorTree(node->right)

	struct tree *temp;

	temp = node->right;
	node->right = node->left;
	node->left = temp;


}