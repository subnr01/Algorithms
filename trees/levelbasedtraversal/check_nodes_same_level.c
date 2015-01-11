


// Recursive function to find level of Node 'ptr' in a binary tree
int level(struct Node *root, struct Node *ptr, int lev)
{
    // base cases
    if (root == NULL) return 0;
    if (root == ptr)  return lev;
 
    // Return level if Node is present in left subtree
    int l = level(root->left, ptr, lev+1);
    if (l != 0)  return l;
 
    // Else search in right subtree
    return level(root->right, ptr, lev+1);
}


bool checkLevel(struct Node *root, struct Node *a, struct Node *b)
{

	return(level(root,a,1) == level(root,b,1);

} 