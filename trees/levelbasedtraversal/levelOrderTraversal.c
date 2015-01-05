
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



//Using stack and queue
void printLevelOrder(BinaryTree *root) {
  if (!root) return;
  queue<BinaryTree*> currentLevel, nextLevel;
  currentLevel.push(root);
  while (!currentLevel.empty()) {
    BinaryTree *currNode = currentLevel.front();
    currentLevel.pop();
    if (currNode) {
      cout << currNode->data << " ";
      nextLevel.push(currNode->left);
      nextLevel.push(currNode->right);
    }
    if (currentLevel.empty()) {
      cout << endl;
      swap(currentLevel, nextLevel);
    }
  }
}
