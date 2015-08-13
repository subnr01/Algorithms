

void delete( struct tree * node)
{
	if ( !node)
		return;

	delete (node->left)
	delete(node->right)

	free(node);
	
}