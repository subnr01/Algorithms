METHOD 1(USing height) O(n2)


void printLevelOrder(struct node* root)
{
  int h = height(root);
  int i;
  for(i=1; i<=h; i++)
    printGivenLevel(root, i);
}   

void printGivenLevel(struct node* root, int level)
{
  if(root == NULL)
    return;
  if(level == 1)
    printf("%d ", root->data);
  else if (level > 1)
  {
    printGivenLevel(root->left, level-1);
    printGivenLevel(root->right, level-1);
  }
}

Method 2 (Using queue)

/* Given a binary tree, print its nodes in level order
   using array for implementing queue */
void printLevelOrder(struct node* root)
{
  int rear, front;
  struct node **queue = createQueue(&front, &rear);  
  struct node *temp_node = root; 
 
  while(temp_node)
  {
    printf("%d ", temp_node->data);
 
    /*Enqueue left child */
    if(temp_node->left)
      enQueue(queue, &rear, temp_node->left);
 
    /*Enqueue right child */
    if(temp_node->right)
      enQueue(queue, &rear, temp_node->right);
 
    /*Dequeue node and make it temp_node*/
    temp_node = deQueue(queue, &front);
  }
}

