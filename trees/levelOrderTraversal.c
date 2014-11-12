
void levelOrderTraversal ( struct tree *node)
{
	if (!node)
		return;

	int height;

	height = height(node);


	for (i to height)
	{
		level(node,i)
	}
}

void level ( struct tree* node, int p)
{
	if (p == 0) {
		print node->data;
		return;
	} 	
	level(node->left, p--);
	level(node->right, p++);
}	

