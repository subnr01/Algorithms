/*

Inorder without recursion

*/


/*

Solution

1) Create an empty stack S.
2) Initialize current node as root
3) Push the current node to S and set current = current->left until current is NULL
4) If current is NULL and stack is not empty then 
     a) Pop the top item from stack.
     b) Print the popped item, set current = popped_item->right 
     c) Go to step 3.
5) If current is NULL and stack is empty then we are done.

*/






void inOrder(struct tNode *root)
{
  /* set current to root of binary tree */
  struct tNode *current = root;
  struct sNode *s = NULL;  /* Initialize stack s */
  bool done = 0;
 
  while (!done)
  {
    /* Reach the left most tNode of the current tNode */
    if(current !=  NULL)
    {
      /* place pointer to a tree node on the stack before traversing 
        the node's left subtree */
      push(&s, current);                                               
      current = current->left;  
    }
        
    /* backtrack from the empty subtree and visit the tNode 
       at the top of the stack; however, if the stack is empty,
      you are done */
    else                                                             
    {
      if (!isEmpty(s))
      {
        current = pop(&s);
        printf("%d ", current->data);
 
        /* we have visited the node and its left subtree.
          Now, it's right subtree's turn */
        current = current->right;
      }
      else
        done = 1; 
    }
  } /* end of while */ 
}     